/*jshint globalstrict: true */
/*global require, exports, applicationContext */
'use strict';

var _ = require('underscore'),
  joi = require('joi'),
  internal = require('internal'),
  arangodb = require('org/arangodb'),
  db = arangodb.db,
  qb = require('aqb'),
  Foxx = require('org/arangodb/foxx'),
  errors = require('./errors'),
  cfg = applicationContext.configuration,
  isSystem = (applicationContext.mount.indexOf('/_system/') === 0),
  Session = Foxx.Model.extend({
    schema: {
      _key: joi.string().required(),
      uid: joi.string().optional(),
      sessionData: joi.object().required(),
      userData: joi.object().required(),
      created: joi.number().integer().required(),
      lastAccess: joi.number().integer().required(),
      lastUpdate: joi.number().integer().required()
    }
  }),
  sessions;

if (isSystem) {
  sessions = new Foxx.Repository(
    db._collection('_sessions'),
    {model: Session}
  );
  populateSystemSids();
} else {
  sessions = new Foxx.Repository(
    applicationContext.collection('sessions'),
    {model: Session}
  );
}

function populateSystemSids() {
  try {
    var cursor = internal.db._query(
      qb
      .for('s').in('_sessions')
      .for('u').in('_users')
      .filter(qb.eq('s.uid', 'u._id'))
      .return({sid: 's._key', user: 'u.user'})
    );
    while (cursor.hasNext()) {
      var doc = cursor.next();
      internal.createSid(doc.sid, doc.user);
    }
  } catch (e) {
    require('console').error(e.stack);
  }
}

function generateSessionId() {
  var sid = '';
  if (cfg.sidTimestamp) {
    sid = internal.base64Encode(Number(new Date()));
    if (cfg.sidLength === 0) {
      return sid;
    }
    sid += '-';
  }
  return sid + internal.genRandomAlphaNumbers(cfg.sidLength || 10);
}

function createSession(sessionData) {
  var sid = generateSessionId(cfg),
    now = Number(new Date()),
    session = new Session({
      _key: sid,
      uid: null,
      sessionData: sessionData || {},
      userData: {},
      created: now,
      lastAccess: now,
      lastUpdate: now
    });
  sessions.save(session);
  return session;
}

function getSession(sid) {
  var session;
  db._executeTransaction({
    collections: {
      read: [sessions.collection.name()],
      write: [sessions.collection.name()]
    },
    action: function () {
      try {
        session = sessions.byId(sid);

        if (isSystem) {
          var accessTime = internal.accessSid(sid);

          if (session.get('lastAccess') < accessTime) {
            session.set('lastAccess', accessTime);
          }
        }

        session.enforceTimeout();
      } catch (err) {
        if (
          err instanceof arangodb.ArangoError
            && err.errorNum === arangodb.ERROR_ARANGO_DOCUMENT_NOT_FOUND
        ) {
          throw new errors.SessionNotFound(sid);
        } else {
          throw err;
        }
      }
      var now = Number(new Date());
      sessions.collection.update(session.forDB(), {
        lastAccess: now
      });
      session.set('lastAccess', now);
    }
  });
  return session;
}

function deleteSession(sid) {
  try {
    sessions.removeById(sid);
  } catch (err) {
    if (
      err instanceof arangodb.ArangoError
        && err.errorNum === arangodb.ERROR_ARANGO_DOCUMENT_NOT_FOUND
    ) {
      throw new errors.SessionNotFound(sid);
    } else {
      throw err;
    }
  }
  return null;
}

_.extend(Session.prototype, {
  enforceTimeout: function () {
    if (this.hasExpired()) {
      throw new errors.SessionExpired(this.get('_key'));
    }
  },
  hasExpired: function () {
    return this.getTTL() === 0;
  },
  getTTL: function () {
    if (!cfg.timeToLive) {
      return Infinity;
    }
    return Math.max(0, this.getExpiry() - Date.now());
  },
  getExpiry: function () {
    if (!cfg.timeToLive) {
      return Infinity;
    }
    var prop = cfg.ttlType;
    if (!prop || !this.get(prop)) {
      prop = 'created';
    }
    return this.get(prop) + cfg.timeToLive;
  },
  setUser: function (user) {
    var session = this;
    if (user) {
      session.set('uid', user.get('_id'));
      session.set('userData', user.get('userData'));

      if (isSystem) {
        internal.createSid(session.get('_key'), user.get('user'));
      }
    } else {
      delete session.attributes.uid;
      session.set('userData', {});

      if (isSystem) {
        internal.cleanSid(session.get('_key'));
      }
    }
    return session;
  },
  save: function () {
    var session = this,
      now = Number(new Date());
    session.set('lastAccess', now);
    session.set('lastUpdate', now);
    sessions.replace(session);
    return session;
  },
  delete: function () {
    var session = this,
      now = Number(new Date());
    session.set('lastAccess', now);
    session.set('lastUpdate', now);
    try {
      var key = session.get('_key');
      deleteSession(key);

      if (isSystem) {
        internal.clearSid(key);
      }
      return true;
    } catch (e) {
      if (e instanceof errors.SessionNotFound) {
        return false;
      }
      throw e;
    }
  }
});

exports.create = createSession;
exports.get = getSession;
exports.delete = deleteSession;
exports.errors = errors;
exports.repository = sessions;
exports._generateSessionId = generateSessionId;
