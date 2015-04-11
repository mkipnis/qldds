#
#   Copyright (C) 2013 Mike Kipnis
#
#   This file is part of QLDDS, a free-software/open-source library
#   for utilization of QuantLib in the distributed envrionment via DDS.
#
#   QLDDS is free software: you can redistribute it and/or modify it
#   under the terms of the QLDDS license.  You should have received a
#   copy of the license along with this program; if not, please email
#   <dev@qldds.org>. The license is also available online at
#   <http://qldds.org/qldds-license/>.
#
#   This program is distributed in the hope that it will be useful, but WITHOUT
#   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#   FOR A PARTICULAR PURPOSE.  See the license for more details.
#

import sys
import getopt
import os
import shutil, errno
import subprocess
import logging

USAGE = """
Arguments :
--type - Compiler type : gnuace, vc9, vc10
--realclean : Perform real clean true or false
--java : build java wrappers true or false
"""

# Logger
logging.basicConfig(filename='build.log', filemode='w',
	level=logging.DEBUG,format='%(asctime)s %(message)s'  )

# Global Variables
ace_root=""
qldds_root=""

def set_dependencies():
    global ace_root, qldds_root
    
    ace_root = os.getenv("ACE_ROOT")
    qldds_root = os.getenv("QLDDS_ROOT")

    if not ace_root or not qldds_root:
       print( "ERROR: ACE_ROOT and/or QLDDS_ROOT environmental variable are not setup\nPlease make sure the project was configured and environment file was sourced in.\n" )
       sys.exit(1)

def usage():
    print( USAGE % { 'scriptName' : sys.argv[0] } )
    sys.exit(1)

def exec_cmd( cmd_args, log_output = True ):
   logging.info( cmd_args )
   use_shell = False 
   if os.name == 'nt': # Windows
     use_shell = True

   if log_output:
     result = None
     proc = subprocess.Popen( cmd_args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell = use_shell )
     while( result == None ):
       result = proc.poll();
       for line in proc.stdout:
         print( line )
         logging.info( line )
     if proc.returncode != 0:
       logging.error(proc.stdout.readlines())
       exit(0)
   else:
     try:
       subprocess.check_call( cmd_args, shell=use_shell )
     except subprocess.CalledProcessError as e:
       logging.error(e)
       exit(0)

def build_qldds_utils( compilerType, realclean = True ):
    global ace_root, qldds_root
    logging.info("building QLDDS Utils : " + compilerType )

    os.chdir(qldds_root+'/qldds_utils')

    exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType, "qldds_utils.mwc"], False )

    if os.name == 'nt':
      if realclean == True:
        exec_cmd( ["msbuild.exe","qldds_utils.sln", "/t:clean"] )
      exec_cmd( ["msbuild.exe","qldds_utils.sln"] )
    else:
      if realclean==True:
         exec_cmd(["make","realclean"])
      exec_cmd(["make"])

def build_qldds_utils_java( compilerType, realclean = True ):
    global ace_root, qldds_root
    logging.info("building QLDDS Utils : " + compilerType )

    os.chdir(qldds_root+'/qldds_utils')

    exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType, "qldds_utils_java.mwc"], False )

    if os.name == 'nt':
      if realclean == True:
        exec_cmd( ["msbuild.exe","qldds_utils_java.sln", "/t:clean"] )
      exec_cmd( ["msbuild.exe","qldds_utils_java.sln"] )
    else:
      if realclean==True:
         exec_cmd(["make","realclean"])
      exec_cmd(["make"])

def build_qldds_dds_addins( compilerType, realclean = True ):
    global ace_root, qldds_root
    logging.info( "Building QLDDS Addins" )

    os.chdir( qldds_root+'/Addins/OpenDDS/' )

    if os.name == 'nt': # Windows
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS_vc.mwc"], False )
      if realclean == True:
        exec_cmd( ["msbuild.exe","QLDDS_vc.sln", "/t:clean"] )
      exec_cmd( ["msbuild.exe","QLDDS_vc.sln"] )

      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDSDataReaders_vc.mwc"] )
      if realclean == True:
        exec_cmd( ["msbuild.exe","QLDDSDataReaders_vc.sln", "/t:clean"] )

      exec_cmd( ["msbuild.exe","QLDDSDataReaders_vc.sln"] )
    else:
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS.mwc"], False )
      if realclean == True:
        exec_cmd( ["make","realclean"] )
      exec_cmd( ["make"] )

def build_qldds_dds_addins_java( compilerType, realclean = True ):
    global ace_root, qldds_root
    logging.info( "Building QLDDS Addins" )

    os.chdir( qldds_root+'/Addins/OpenDDS/java' )

    if os.name == 'nt': # Windows
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS_vc.mwc"], False )
      if realclean == True:
        exec_cmd( ["msbuild.exe","QLDDS_vc.sln", "/t:clean"] )
      exec_cmd( ["msbuild.exe","QLDDS_vc.sln"] )

      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDSDataReaders_vc.mwc"] )
      if realclean == True:
        exec_cmd( ["msbuild.exe","QLDDSDataReaders_vc.sln", "/t:clean"] )

      exec_cmd( ["msbuild.exe","QLDDSDataReaders_vc.sln"] )
    else:
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS_Java.mwc"], False )
      if realclean == True:
        exec_cmd( ["make","realclean"] )
      exec_cmd( ["make"] )

def build_example( directory, mwc_prefix, compilerType, realclean = True ):
    global ace_root, qldds_root, logger

    os.chdir( directory )

    if os.name == 'nt':
      prefix = mwc_prefix +"_" + compilerType
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, prefix+".mwc" ] )
      if realclean == True:
        exec_cmd( ["msbuild.exe",prefix+".sln", "/t:clean"] )

      exec_cmd( ["msbuild.exe",prefix+".sln"] )
    else:
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, mwc_prefix+".mwc"] )
      if realclean==True:
        exec_cmd( ["make","realclean"] )
      exec_cmd( ["make"] )


# parse command line arguments
try:

    opts, args = getopt.getopt(sys.argv[1:], 'h',
	 	   ['help','type=','realclean=','java='] )

except getopt.GetoptError:
    usage()

realclean=True
compilerType=''
buildjava=False


for o, v in opts:
    if o == '--type':
       compilerType = v
    elif o == '--realclean':
         if v == 'false':
            realclean = False
    elif o == '--java':
         if v == 'true':
            buildjava = True
    elif o in ('-h','--help'):
      usage()
    else:
      usage()

if compilerType == '':
  if os.name == 'nt':
    framework = os.environ.get('FrameworkVersion')
    print( framework ) 
    if framework[0:4] == 'v4.0':
      compilerType = 'vc10'
    elif framework[0:4] == 'v2.0':
      compilerType = 'vc9'
    else:
      print( "ERROR: Unsupport Visual Studio Framework. Please use Visual Studio 2008 or 2010.");
      sys.exit(1)
  else:
    compilerType = 'gnuace'

logging.info("Starting") 
set_dependencies()

build_qldds_utils( compilerType, realclean )

if buildjava == True:
  build_qldds_utils_java( compilerType, realclean )

build_qldds_dds_addins( compilerType, realclean )

if buildjava == True:
  build_qldds_dds_addins_java( compilerType, realclean )

build_example( qldds_root+'/Examples/InterestRateSwaps',
               'InterestRateSwaps', compilerType, realclean )

build_example( qldds_root+'/Examples/Swaptions',
               'Swaptions', compilerType, realclean )

build_example( qldds_root+'/Examples/EquityOptions',
               'EquityOptions', compilerType, realclean )

