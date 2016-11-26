
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl QLDDS
// ------------------------------
#ifndef QLDDS_EXPORT_H
#define QLDDS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (QLDDS_HAS_DLL)
#  define QLDDS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && QLDDS_HAS_DLL */

#if !defined (QLDDS_HAS_DLL)
#  define QLDDS_HAS_DLL 1
#endif /* ! QLDDS_HAS_DLL */

#if defined (QLDDS_HAS_DLL) && (QLDDS_HAS_DLL == 1)
#  if defined (QLDDS_BUILD_DLL)
#    define QLDDS_Export ACE_Proper_Export_Flag
#    define QLDDS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define QLDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* QLDDS_BUILD_DLL */
#    define QLDDS_Export ACE_Proper_Import_Flag
#    define QLDDS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define QLDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* QLDDS_BUILD_DLL */
#else /* QLDDS_HAS_DLL == 1 */
#  define QLDDS_Export
#  define QLDDS_SINGLETON_DECLARATION(T)
#  define QLDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* QLDDS_HAS_DLL == 1 */

// Set QLDDS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (QLDDS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define QLDDS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define QLDDS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !QLDDS_NTRACE */

#if (QLDDS_NTRACE == 1)
#  define QLDDS_TRACE(X)
#else /* (QLDDS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define QLDDS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (QLDDS_NTRACE == 1) */

#endif /* QLDDS_EXPORT_H */

// End of auto generated file.
