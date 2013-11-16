
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl Straddles
// ------------------------------
#ifndef STRADDLES_EXPORT_H
#define STRADDLES_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (STRADDLES_HAS_DLL)
#  define STRADDLES_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && STRADDLES_HAS_DLL */

#if !defined (STRADDLES_HAS_DLL)
#  define STRADDLES_HAS_DLL 1
#endif /* ! STRADDLES_HAS_DLL */

#if defined (STRADDLES_HAS_DLL) && (STRADDLES_HAS_DLL == 1)
#  if defined (STRADDLES_BUILD_DLL)
#    define Straddles_Export ACE_Proper_Export_Flag
#    define STRADDLES_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define STRADDLES_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* STRADDLES_BUILD_DLL */
#    define Straddles_Export ACE_Proper_Import_Flag
#    define STRADDLES_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define STRADDLES_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* STRADDLES_BUILD_DLL */
#else /* STRADDLES_HAS_DLL == 1 */
#  define Straddles_Export
#  define STRADDLES_SINGLETON_DECLARATION(T)
#  define STRADDLES_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* STRADDLES_HAS_DLL == 1 */

// Set STRADDLES_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (STRADDLES_NTRACE)
#  if (ACE_NTRACE == 1)
#    define STRADDLES_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define STRADDLES_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !STRADDLES_NTRACE */

#if (STRADDLES_NTRACE == 1)
#  define STRADDLES_TRACE(X)
#else /* (STRADDLES_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define STRADDLES_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (STRADDLES_NTRACE == 1) */

#endif /* STRADDLES_EXPORT_H */

// End of auto generated file.
