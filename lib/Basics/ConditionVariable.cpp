////////////////////////////////////////////////////////////////////////////////
/// @brief Condition Variable
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Achim Brandt
/// @author Copyright 2014, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2008-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "ConditionVariable.h"

using namespace triagens::basics;

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief constructs a condition variable
////////////////////////////////////////////////////////////////////////////////

ConditionVariable::ConditionVariable ()
  : _condition() {
  TRI_InitCondition(&_condition);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief deletes the condition variable
////////////////////////////////////////////////////////////////////////////////

ConditionVariable::~ConditionVariable () {
  TRI_DestroyCondition(&_condition);
}

// -----------------------------------------------------------------------------
// --SECTION--                                                    public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief locks the condition variable
////////////////////////////////////////////////////////////////////////////////

void ConditionVariable::lock () {
  TRI_LockCondition(&_condition);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief releases the lock on the condition variable
////////////////////////////////////////////////////////////////////////////////

void ConditionVariable::unlock () {
  TRI_UnlockCondition(&_condition);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief waits for an event
////////////////////////////////////////////////////////////////////////////////

void ConditionVariable::wait () {
  TRI_WaitCondition(&_condition);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief waits for an event with timeout in micro seconds
////////////////////////////////////////////////////////////////////////////////

bool ConditionVariable::wait (uint64_t delay) {
  return TRI_TimedWaitCondition(&_condition, delay);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief signals all waiting threads
////////////////////////////////////////////////////////////////////////////////

void ConditionVariable::broadcast () {
  TRI_BroadcastCondition(&_condition);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief signals a waiting thread
////////////////////////////////////////////////////////////////////////////////

void ConditionVariable::signal () {
  TRI_SignalCondition(&_condition);
}

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End: