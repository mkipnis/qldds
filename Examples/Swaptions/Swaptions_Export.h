
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl Swaptions
// ------------------------------
#ifndef SWAPTIONS_EXPORT_H
#define SWAPTIONS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (SWAPTIONS_HAS_DLL)
#  define SWAPTIONS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && SWAPTIONS_HAS_DLL */

#if !defined (SWAPTIONS_HAS_DLL)
#  define SWAPTIONS_HAS_DLL 1
#endif /* ! SWAPTIONS_HAS_DLL */

#if defined (SWAPTIONS_HAS_DLL) && (SWAPTIONS_HAS_DLL == 1)
#  if defined (SWAPTIONS_BUILD_DLL)
#    define Swaptions_Export ACE_Proper_Export_Flag
#    define SWAPTIONS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define SWAPTIONS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* SWAPTIONS_BUILD_DLL */
#    define Swaptions_Export ACE_Proper_Import_Flag
#    define SWAPTIONS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define SWAPTIONS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* SWAPTIONS_BUILD_DLL */
#else /* SWAPTIONS_HAS_DLL == 1 */
#  define Swaptions_Export
#  define SWAPTIONS_SINGLETON_DECLARATION(T)
#  define SWAPTIONS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* SWAPTIONS_HAS_DLL == 1 */

// Set SWAPTIONS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (SWAPTIONS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define SWAPTIONS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define SWAPTIONS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !SWAPTIONS_NTRACE */

#if (SWAPTIONS_NTRACE == 1)
#  define SWAPTIONS_TRACE(X)
#else /* (SWAPTIONS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define SWAPTIONS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (SWAPTIONS_NTRACE == 1) */

#endif /* SWAPTIONS_EXPORT_H */

// End of auto generated file.
