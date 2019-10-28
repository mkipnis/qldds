import sys
import getopt
import os
import shutil, errno

USAGE_ERROR = """
usage: %(scriptName)s --dds_dir --boost_dir --quantlib_dir --oh_dir --qladdin_dir
    Arguments that specify paths to the following components : 
    --dds_dir - Installation directory of OpenDDS
    --boost_dir - Installation directory of Boost
    --quantlib_dir - Installation directory of QuantLib
    --oh_dir - Intallation directory of ObjectHandler
    --qladdin_dir - Installation directory of QuantLibAddin"""

def usage():
    print( USAGE_ERROR % { 'scriptName' : sys.argv[0] } )
    sys.exit(1)

# parse command line arguments
try:

    opts, args = getopt.getopt(sys.argv[1:], 'hdbqgoa', ['help','dds_dir=','boost_dir=', 'quantlib_dir=', 'oh_dir=','qladdin_dir='] )

except getopt.GetoptError:
    usage()

ddsDir=''
boostDir=''
quantlibDir = ''
ohDir=''
qlAddinDir=''

if os.name == 'nt':
	print("Windows NT is not support by this version of QLDDS, Please use the following branch : qldds-qladdin-1.12");
	exit(0);

print( "-------- Environment Settings ----------" )

for o, v in opts:
    if o == '--dds_dir':
        ddsDir = v
        print( "OpenDDS dir : " + ddsDir )
    elif o == '--boost_dir':
        boostDir = v
        print( "Boost dir : " + boostDir )
    elif o == '--quantlib_dir':
        quantlibDir = v
        print( "QuantLib dir : " + quantlibDir )
    elif o == '--oh_dir':
        ohDir = v
        print( "ObjectHandler dir : " + ohDir ) 
    elif o == '--qladdin_dir':
        qlAddinDir = v
        print( "QuantLibAddin dir : " + qlAddinDir )
    elif o in ('-h', '--help'):
        usage()
    else:
        usage()

print( "----------------------------------------" )

if not len(ddsDir):
  print( "ERROR : Location of OpenDDS [--qldds_dir] is not specified." )
  usage() 

if not len(boostDir):
  print( "ERROR : Location of Boost [--boost_dir] is not specified." ) 
  usage() 

if not len(quantlibDir):
  print( "ERROR : Location of QuantLib [--quantlib_dir] is not specified." )
  usage() 

if not len(ohDir):
  print( "ERROR : Location of GenSrc [--oh_dir] is not specified." )
  usage() 

if not len(qlAddinDir):
  print( "ERROR : Location of GenSrc [--qladdin_dir] is not specified." )
  usage()

env_file='qldds_env'
path=''
lib_path=''
path_separator='' 
open_dds_env=''
qldds_root=os.getcwd()
export = ''

# Unix
if os.name == 'posix':
  env_file += '.sh' 
  path_separator=':'
  export = 'export'
  open_dds_env='. ' + ddsDir + '/setenv.sh' 

  path = 'export PATH=${PATH}' + path_separator + '${ACE_ROOT}/bin/'

  if sys.platform == 'darwin':
    lib_path='export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}' + path_separator 
  else:
    lib_path='export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}' + path_separator 
   
  lib_path += qldds_root + '/qldds_utils/' + path_separator
  lib_path += qldds_root + '/Addins/OpenDDS/' + path_separator

  lib_path += quantlibDir + '/lib' + path_separator
  lib_path += boostDir + '/lib' + path_separator
  lib_path += ohDir + '/lib' + path_separator
  lib_path += qlAddinDir + '/lib' + path_separator

try:
  file = open(env_file, 'w')
  

  file.write( export + ' QLDDS_ROOT=' + qldds_root + '\n' )
  file.write( export + ' QUANTLIB_ROOT=' + quantlibDir + '\n' )
  file.write( export + ' BOOST_ROOT=' + boostDir + '\n' )
  file.write( export + ' OH_ROOT=' + ohDir + '\n' )
  file.write( export + ' QUANTLIB_ADDIN_ROOT=' + qlAddinDir + '\n\n' )

  file.write( path + '\n' )
  file.write( lib_path + '\n' )

  file.write( open_dds_env + '\n\n' )

  file.close()

except IOError:
  print( 'Could not create : [' + env_file + ']' )
  exit(1)

print( "Configuration complete.\n\n" )

environment_load = ". ./" + env_file;
create_workspace_command = "$ACE_ROOT/bin/mwc.pl -type gnuace QLDDS.mwc";

print("Loading Environment file : " + env_file + " and creating workspace : " + create_workspace_command);
os.system( environment_load + ";" + create_workspace_command + ";" );

print("Please load environment file : " + environment_load + " and run make");
