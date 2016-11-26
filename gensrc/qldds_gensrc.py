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


USAGE_ERROR = """
usage: %(scriptName)s --oh_dir --qladdin_dir
    --oh_dir specifies the path to the root directory of the
    ObjectHandler source code tree. 
    --gensrc_dir specifies the path to the root directory of the
    GenSrc source code tree. 
    --qladdin_dir specifies the path to the root directory of the
    QuantLibAddin source code tree."""

def usage():
    print( USAGE_ERROR % { 'scriptName' : sys.argv[0] } )
    sys.exit(1)

def generateCode():

    global dds_addin
    log.Log.instance().logMessage('begin ...')
    categoryList = categorylist.CategoryList()
    enumerationList = enumerationlist.EnumerationList()
    categoryList.init(enumerationList)

    dds_addin = utilities.serializeObject(opendds.OpenDDSAddin, 'metadata/addins/opendds')

    dds_addin.generate(categoryList, enumerationList)
    log.Log.instance().logMessage('end')

def generateSummary():
    global dds_addin

    LINE_HEADER1 = '''addin           unchanged   updated     created     total'''
    LINE_HEADER2 = '''=============== =========== =========== =========== ==========='''
    LINE_FORMAT = '%-15s%12d%12d%12d%12d'

    log.Log.instance().logMessage()
    log.Log.instance().logMessage(LINE_HEADER1)
    log.Log.instance().logMessage(LINE_HEADER2)

    totalAll = 0
    totalUnchanged = 0
    totalUpdated = 0
    totalCreated = 0

    totalLine = dds_addin.unchanged() + dds_addin.updated() + dds_addin.created()
    totalUnchanged += dds_addin.unchanged()
    totalUpdated += dds_addin.updated()
    totalCreated += dds_addin.created()
    totalAll += totalLine
    msg = LINE_FORMAT % (dds_addin.name(), dds_addin.unchanged(),
             dds_addin.updated(), dds_addin.created(), totalLine)
    log.Log.instance().logMessage(msg)


# parse command line arguments
try:
    opts, args = getopt.getopt(sys.argv[1:], 'ogha', ['help', 'oh_dir=','qladdin_dir=','gensrc_dir='] )
except getopt.GetoptError:
    usage()

ohDir=''
gensrcDir=''
qlAddingDir=''

for o, v in opts:
    if o == '--oh_dir':
        ohDir = v
    elif o == '--gensrc_dir':
        gensrcDir = v   
    elif o == '--qladdin_dir':
        qlAddingDir = v   
    elif o in ('-h', '--help'):
        usage()
    else:
        usage()

print( ohDir )

if not len(ohDir) or not len(qlAddingDir) or not len(gensrcDir):
    usage()


#copy types and functions
if os.path.exists('metadata/types/'):
    shutil.rmtree('metadata/types/', ignore_errors=True)
shutil.copytree(qlAddingDir+'/gensrc/metadata/types/', 'metadata/types/')

#TODO : make optional
#if os.path.exists('metadata/functions/'):
#    shutil.rmtree('metadata/functions/', ignore_errors=True)
#shutil.copytree(qlAddingDir+'/gensrc/metadata/functions/', 'metadata/functions/')

sys.path.insert(0, gensrcDir)

from gensrc.exceptions import excepthook
from gensrc.configuration import initialization
from gensrc.categories import categorylist
from gensrc.enumerations import enumerationlist
from gensrc.utilities import utilities
from gensrc.utilities import log
from gensrc.configuration import environment

import opendds

# Initialize the environment.
initialization.init(ohDir)
generateCode()
generateSummary()
