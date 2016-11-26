
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl CurveBuilder
// ------------------------------
#ifndef CURVEBUILDER_EXPORT_H
#define CURVEBUILDER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (CURVEBUILDER_HAS_DLL)
#  define CURVEBUILDER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && CURVEBUILDER_HAS_DLL */

#if !defined (CURVEBUILDER_HAS_DLL)
#  define CURVEBUILDER_HAS_DLL 1
#endif /* ! CURVEBUILDER_HAS_DLL */

#if defined (CURVEBUILDER_HAS_DLL) && (CURVEBUILDER_HAS_DLL == 1)
#  if defined (CURVEBUILDER_BUILD_DLL)
#    define CurveBuilder_Export ACE_Proper_Export_Flag
#    define CURVEBUILDER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define CURVEBUILDER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* CURVEBUILDER_BUILD_DLL */
#    define CurveBuilder_Export ACE_Proper_Import_Flag
#    define CURVEBUILDER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define CURVEBUILDER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* CURVEBUILDER_BUILD_DLL */
#else /* CURVEBUILDER_HAS_DLL == 1 */
#  define CurveBuilder_Export
#  define CURVEBUILDER_SINGLETON_DECLARATION(T)
#  define CURVEBUILDER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* CURVEBUILDER_HAS_DLL == 1 */

// Set CURVEBUILDER_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (CURVEBUILDER_NTRACE)
#  if (ACE_NTRACE == 1)
#    define CURVEBUILDER_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define CURVEBUILDER_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !CURVEBUILDER_NTRACE */

#if (CURVEBUILDER_NTRACE == 1)
#  define CURVEBUILDER_TRACE(X)
#else /* (CURVEBUILDER_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define CURVEBUILDER_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (CURVEBUILDER_NTRACE == 1) */

#endif /* CURVEBUILDER_EXPORT_H */

// End of auto generated file.
