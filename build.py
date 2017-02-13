
"""
   Copyright (C) 2016 Mike Kipnis

   This file is part of QLDDS, a free-software/open-source library
   for utilization of QuantLib in the distributed envrionment via DDS.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
"""

import sys
import getopt
import os
import shutil, errno
import subprocess
import logging

USAGE = """
Arguments :
--type - Compiler type : gnuace, vc9, vc10
--realclean=true/false : Perform real clean true or false
--java=true/false : build java wrappers true or false
--realcleanonlue : only cleans all packages
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

def realclean_all( compilerType, java ):
    global ace_root, qldds_root

    os.chdir(qldds_root+'/qldds_utils')
    exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType, "qldds_utils.mwc"], False ) 
    if os.name == 'nt':
      exec_cmd( ["msbuild.exe","qldds_utils.sln", "/t:clean"] )
    else:
      exec_cmd(["make","realclean"])

    os.chdir( qldds_root+'/Addins/OpenDDS/' )
    if os.name == 'nt': # Windows
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS_vc.mwc"], False )
      exec_cmd( ["msbuild.exe","QLDDS_vc.sln", "/t:clean"] )
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDSDataReaders_vc.mwc"] )
      exec_cmd( ["msbuild.exe","QLDDSDataReaders_vc.sln", "/t:clean"] )
    else:
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS.mwc"], False )
      exec_cmd( ["make","realclean"] )

    realclean_example( qldds_root+'/Examples/InterestRateSwaps', 'InterestRateSwaps', compilerType )
    realclean_example( qldds_root+'/Examples/Swaptions', 'Swaptions', compilerType )
    realclean_example( qldds_root+'/Examples/EquityOptions', 'EquityOptions', compilerType )

    if buildjava == False:
      return

    if os.name != 'nt': 
      os.chdir(qldds_root+'/java/qldds_utils')
      exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType, "qldds_utils_java.mwc"], False ) 
      exec_cmd(["make","realclean"])

      os.chdir( qldds_root+'/java/Addins/OpenDDS/' )
      exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType], False )
      exec_cmd(["make","realclean"]) 

      os.chdir( qldds_root+'/java/Examples/CurveBuilder/' )
      exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType], False )
      exec_cmd(["make","realclean"])

def buildall( compilerType, build_java ):
    global ace_root, qldds_root

    os.chdir(qldds_root+'/qldds_utils')
    exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType, "qldds_utils.mwc"], False )
    if os.name == 'nt':
      exec_cmd( ["msbuild.exe","qldds_utils.sln"] )
    else:
      exec_cmd(["make"])

    os.chdir( qldds_root+'/Addins/OpenDDS/' )
    if os.name == 'nt': # Windows
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS_vc.mwc"], False )
      exec_cmd( ["msbuild.exe","QLDDS_vc.sln"] )
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDSDataReaders_vc.mwc"] )
      exec_cmd( ["msbuild.exe","QLDDSDataReaders_vc.sln"] )
    else:
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, "QLDDS.mwc"], False )
      exec_cmd( ["make"] )

    #build_example( qldds_root+'/Examples/InterestRateSwaps', 'InterestRateSwaps', compilerType )
    #build_example( qldds_root+'/Examples/Swaptions', 'Swaptions', compilerType )
    #build_example( qldds_root+'/Examples/EquityOptions', 'EquityOptions', compilerType )

    if buildjava == False:
      return

    if os.name != 'nt':
      os.chdir(qldds_root+'/java/qldds_utils')
      exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType, "qldds_utils_java.mwc"], False )
      exec_cmd(["make"])

      os.chdir( qldds_root+'/java/Addins/OpenDDS/' )
      exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType], False )
      exec_cmd(["make"])

    os.chdir( qldds_root+'/java/Examples/CurveBuilder/' )
    exec_cmd([ace_root+'/bin/mwc.pl','-type', compilerType], False )
    os.chdir( qldds_root+'/java/Examples/CurveBuilder/CurveBuilderIDL/' )
    exec_cmd(["make"])
    os.chdir( qldds_root+'/java/Examples/CurveBuilder/' )
    exec_cmd(["make"])


def realclean_example( directory, mwc_prefix, compilerType ):
    global ace_root, qldds_root, logger

    os.chdir( directory )

    if os.name == 'nt':
      prefix = mwc_prefix +"_" + compilerType
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, prefix+".mwc" ] )
      exec_cmd( ["msbuild.exe",prefix+".sln", "/t:clean"] )
    else:
      exec_cmd( [ace_root+'/bin/mwc.pl',"-type", compilerType, mwc_prefix+".mwc"] )
      exec_cmd( ["make","realclean"] )

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
	 	   ['help','type=','realclean=','java=','realcleanonly'] )

except getopt.GetoptError:
    usage()

realclean=True
compilerType=''
buildjava=False
realcleanOnly=False



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
    elif o == '--realcleanonly': 
      realcleanOnly = True
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

if realcleanOnly == True:
  realclean_all(compilerType, buildjava)
  sys.exit(0)

if realclean == True:
  realclean_all(compilerType, buildjava)

buildall(compilerType, buildjava)
