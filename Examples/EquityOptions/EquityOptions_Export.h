
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl EquityOptions
// ------------------------------
#ifndef EQUITYOPTIONS_EXPORT_H
#define EQUITYOPTIONS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (EQUITYOPTIONS_HAS_DLL)
#  define EQUITYOPTIONS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && EQUITYOPTIONS_HAS_DLL */

#if !defined (EQUITYOPTIONS_HAS_DLL)
#  define EQUITYOPTIONS_HAS_DLL 1
#endif /* ! EQUITYOPTIONS_HAS_DLL */

#if defined (EQUITYOPTIONS_HAS_DLL) && (EQUITYOPTIONS_HAS_DLL == 1)
#  if defined (EQUITYOPTIONS_BUILD_DLL)
#    define EquityOptions_Export ACE_Proper_Export_Flag
#    define EQUITYOPTIONS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define EQUITYOPTIONS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* EQUITYOPTIONS_BUILD_DLL */
#    define EquityOptions_Export ACE_Proper_Import_Flag
#    define EQUITYOPTIONS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define EQUITYOPTIONS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* EQUITYOPTIONS_BUILD_DLL */
#else /* EQUITYOPTIONS_HAS_DLL == 1 */
#  define EquityOptions_Export
#  define EQUITYOPTIONS_SINGLETON_DECLARATION(T)
#  define EQUITYOPTIONS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* EQUITYOPTIONS_HAS_DLL == 1 */

// Set EQUITYOPTIONS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (EQUITYOPTIONS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define EQUITYOPTIONS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define EQUITYOPTIONS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !EQUITYOPTIONS_NTRACE */

#if (EQUITYOPTIONS_NTRACE == 1)
#  define EQUITYOPTIONS_TRACE(X)
#else /* (EQUITYOPTIONS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define EQUITYOPTIONS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (EQUITYOPTIONS_NTRACE == 1) */

#endif /* EQUITYOPTIONS_EXPORT_H */

// End of auto generated file.
