////////////////////////////////////////////////////////////////////////////////
/// @brief basic string functions
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
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
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2011-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_BASICS_C_STRINGS_H
#define TRIAGENS_BASICS_C_STRINGS_H 1

#include "BasicsC/common.h"

#include "BasicsC/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Strings
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief convert an ASCII string to lower case
///
/// Note: this works with ASCII characters only. No umlauts, no UTF-8 characters
/// tolower and toupper of ctype.h are not used because they depend on locale
////////////////////////////////////////////////////////////////////////////////

char* TRI_LowerAsciiStringZ (TRI_memory_zone_t*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief convert an ASCII string to lower case
///
/// Note: this works with ASCII characters only. No umlauts, no UTF-8 characters
/// tolower and toupper of ctype.h are not used because they depend on locale
////////////////////////////////////////////////////////////////////////////////

char* TRI_LowerAsciiString (char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief convert an ASCII string to upper case
///
/// Note: this works with ASCII characters only. No umlauts, no UTF-8 characters
/// tolower and toupper of ctype.h are not used because they depend on locale
////////////////////////////////////////////////////////////////////////////////

char* TRI_UpperAsciiStringZ (TRI_memory_zone_t*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief convert an ASCII string to upper case
///
/// Note: this works with ASCII characters only. No umlauts, no UTF-8 characters
/// tolower and toupper of ctype.h are not used because they depend on locale
////////////////////////////////////////////////////////////////////////////////

char* TRI_UpperAsciiString (char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief tests if ASCII strings are equal
////////////////////////////////////////////////////////////////////////////////

bool TRI_EqualString (char const* left, char const* right);

////////////////////////////////////////////////////////////////////////////////
/// @brief tests if ASCII strings are equal
////////////////////////////////////////////////////////////////////////////////

bool TRI_EqualString2 (char const* left, char const* right, size_t n);

////////////////////////////////////////////////////////////////////////////////
/// @brief tests if ASCII strings are equal ignoring case
////////////////////////////////////////////////////////////////////////////////

bool TRI_CaseEqualString (char const* left, char const* right);

////////////////////////////////////////////////////////////////////////////////
/// @brief tests if ASCII strings are equal ignoring case
////////////////////////////////////////////////////////////////////////////////

bool TRI_CaseEqualString2 (char const* left, char const* right, size_t n);

////////////////////////////////////////////////////////////////////////////////
/// @brief tests if second string is prefix of the first
////////////////////////////////////////////////////////////////////////////////

bool TRI_IsPrefixString (char const* full, char const* prefix);

////////////////////////////////////////////////////////////////////////////////
/// @brief duplicates a string, without using a memory zone
///
/// This function can be used when strings need to be returned to other system
/// functions that do not use memory zones
////////////////////////////////////////////////////////////////////////////////

char* TRI_SystemDuplicateString (char const* value);

////////////////////////////////////////////////////////////////////////////////
/// @brief duplicates a string
////////////////////////////////////////////////////////////////////////////////

char* TRI_DuplicateString (char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief duplicates a string
////////////////////////////////////////////////////////////////////////////////

char* TRI_DuplicateStringZ (TRI_memory_zone_t*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief duplicates a string of given length
////////////////////////////////////////////////////////////////////////////////

char* TRI_DuplicateString2 (char const*, size_t length);

////////////////////////////////////////////////////////////////////////////////
/// @brief duplicates a string of given length
////////////////////////////////////////////////////////////////////////////////

char* TRI_DuplicateString2Z (TRI_memory_zone_t*, char const*, size_t length);

////////////////////////////////////////////////////////////////////////////////
/// @brief appends text to a string
////////////////////////////////////////////////////////////////////////////////

void TRI_AppendString (char**, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief copies a string
///
/// Copy string of maximal length. Always append a '\0'.
////////////////////////////////////////////////////////////////////////////////

void TRI_CopyString (char* dst, char const* src, size_t length);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate two strings
////////////////////////////////////////////////////////////////////////////////

char* TRI_Concatenate2String (char const*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate two strings using a memory zone
////////////////////////////////////////////////////////////////////////////////

char* TRI_Concatenate2StringZ (TRI_memory_zone_t*, char const*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate two strings, with known lengths
////////////////////////////////////////////////////////////////////////////////

char* TRI_ConcatenateSized2String (char const*, size_t, char const*, size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate two strings, with known lengths, using a memory zone
////////////////////////////////////////////////////////////////////////////////

char* TRI_ConcatenateSized2StringZ (TRI_memory_zone_t*, 
                                    char const*, 
                                    size_t, 
                                    char const*, 
                                    size_t); 

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate three strings
////////////////////////////////////////////////////////////////////////////////

char* TRI_Concatenate3String (char const*, char const*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate three strings using a memory zone
////////////////////////////////////////////////////////////////////////////////

char* TRI_Concatenate3StringZ (TRI_memory_zone_t*, char const*, char const*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate four strings
////////////////////////////////////////////////////////////////////////////////

char* TRI_Concatenate4String (char const*, char const*, char const*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate five strings
////////////////////////////////////////////////////////////////////////////////

char* TRI_Concatenate5String (char const*, char const*, char const*, char const*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief concatenate six strings
////////////////////////////////////////////////////////////////////////////////

char* TRI_Concatenate6String (char const*, char const*, char const*, char const*, char const*, char const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief splits a string
////////////////////////////////////////////////////////////////////////////////

TRI_vector_string_t TRI_SplitString (char const* source, char delim);

////////////////////////////////////////////////////////////////////////////////
/// @brief splits a string, using more than one delimiter
////////////////////////////////////////////////////////////////////////////////

TRI_vector_string_t TRI_Split2String (char const* source, char const* delim);

////////////////////////////////////////////////////////////////////////////////
/// @brief frees a string
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_MAINTAINER_MODE
#define TRI_FreeString(a,b) TRI_FreeStringZ((a),(b),__FILE__,__LINE__)
void TRI_FreeStringZ (TRI_memory_zone_t*, char*, char const* file, int line);
#else
void TRI_FreeString (TRI_memory_zone_t*, char*);
#endif

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                     STRING ESCAPE
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Strings
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief converts into printable representation
////////////////////////////////////////////////////////////////////////////////

char* TRI_PrintableString (char const*, size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief converts into hex reqpresentation
////////////////////////////////////////////////////////////////////////////////

char* TRI_EncodeHexString (char const* source, size_t sourceLen, size_t* dstLen);

////////////////////////////////////////////////////////////////////////////////
/// @brief converts from hex reqpresentation
////////////////////////////////////////////////////////////////////////////////

char* TRI_DecodeHexString (char const* source, size_t sourceLen, size_t* dstLen);

////////////////////////////////////////////////////////////////////////////////
/// @brief sha256 of a string
////////////////////////////////////////////////////////////////////////////////

char* TRI_SHA256String (char const* source, size_t sourceLen, size_t* dstLen);

////////////////////////////////////////////////////////////////////////////////
/// @brief escapes special characters using C escapes
////////////////////////////////////////////////////////////////////////////////

char* TRI_EscapeControlsCString (TRI_memory_zone_t*, 
                                 char const* in, 
                                 size_t inLength, 
                                 size_t* outLength, 
                                 bool appendNewline);

////////////////////////////////////////////////////////////////////////////////
/// @brief escapes special characters using C escapes
///
/// This method escapes a character string by replacing the unprintable
/// characters by a C sequences.
////////////////////////////////////////////////////////////////////////////////

char* TRI_EscapeCString (char const* in, size_t inLength, size_t* outLength);

////////////////////////////////////////////////////////////////////////////////
/// @brief escapes special characters using unicode escapes
///
/// This method escapes an UTF-8 character string by replacing the unprintable
/// characters by a \\uXXXX sequence. Set escapeSlash to true in order to also
/// escape the character '/'.
////////////////////////////////////////////////////////////////////////////////

char* TRI_EscapeUtf8String (char const* in, 
                            size_t inLength, 
                            bool escapeSlash, 
                            size_t* outLength,
                            bool);

////////////////////////////////////////////////////////////////////////////////
/// @brief escapes special characters using unicode escapes
////////////////////////////////////////////////////////////////////////////////

char* TRI_EscapeUtf8StringZ (TRI_memory_zone_t*, 
                             char const* in, 
                             size_t inLength, 
                             bool escapeSlash, 
                             size_t* outLength, 
                             bool);

////////////////////////////////////////////////////////////////////////////////
/// @brief unescapes unicode escape sequences
///
/// This method decodes a UTF-8 character string by replacing the \\uXXXX
/// sequence by unicode characters and representing them as UTF-8 sequences.
////////////////////////////////////////////////////////////////////////////////

char* TRI_UnescapeUtf8String (char const* in, size_t inLength, size_t* outLength);

////////////////////////////////////////////////////////////////////////////////
/// @brief unescapes unicode escape sequences
////////////////////////////////////////////////////////////////////////////////

char* TRI_UnescapeUtf8StringZ (TRI_memory_zone_t*, char const* in, size_t inLength, size_t* outLength);

////////////////////////////////////////////////////////////////////////////////
/// @brief determine the number of characters in a UTF-8 string
/// the UTF-8 string must be well-formed and end with a NUL terminator
////////////////////////////////////////////////////////////////////////////////

size_t TRI_CharLengthUtf8String (const char*);

////////////////////////////////////////////////////////////////////////////////
/// @brief get the string end position for a leftmost prefix of a UTF-8 string
/// eg. when specifying (müller, 2), the return value will be a pointer to the
/// first "l".
/// the UTF-8 string must be well-formed and end with a NUL terminator
////////////////////////////////////////////////////////////////////////////////

char* TRI_PrefixUtf8String (const char*, const uint32_t);




////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
