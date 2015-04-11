#
#   Copyright (C) 2015 Mike Kipnis
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


import os,sys

from gensrc.addins import addin
from gensrc.addins import cppexceptions
from gensrc.configuration import environment
from gensrc.categories import category
from gensrc.utilities import log
from gensrc.utilities import common

from gensrc.utilities import outputfile

class OpenDDSAddin(addin.Addin):
    """Generate source code for OpenDDS/C++ addin."""

    #############################################
    # public interface
    #############################################

    def generate(self, categoryList, enumerationList):
        """Generate source code for OpenDDS/C++ addin."""

        self.categoryList_ = categoryList
        self.enumerationList_ = enumerationList

        log.Log.instance().logMessage(' begin generating %s...' % self.name_)
        self.generateFunctions()
        log.Log.instance().logMessage(' done generating %s.' % self.name_)

    def generateFunctions(self):
        """Generate source code for all functions in all categories."""

        loopIncludes = ''
        mpcbuffer = ''
        mpcdatareaderbuffer = ''
        mpcdatareaderbufferNT = ''
	mpcbufferJava = ''
        idlfiles = ''
	mwcbufferJava = ''

        for cat in self.categoryList_.categories("Cpp",
            self.coreCategories_, self.addinCategories_):
            
            idlfilesTypeSupport = '' 
            readersImplHpp = '' 
            readersImplCpp = ''

	    qlAddinName = cat.name()
	    if (cat.name() == 'index') : cat.name_ = 'qlIndex'

            categoryIncludes = cat.includeList(loopIncludes)

	    idlfile = '\t%s.idl\n' % ( cat.name() ) 
	    idlfileTypeSupport = '\t%sTypeSupport.idl\n' % ( cat.name() )

	    readerImplHpp = '\t%sDataReaderListenerImpl.hpp\n' % ( cat.name() ) 
	    readerImplCpp = '\t%sDataReaderListenerImpl.cpp\n' % ( cat.name() )   

            bufferCpp = ''
            bufferHpp = '' 
            bufferIDL = ''	      

            for func in cat.functions("Cpp"): 
                bufferCpp += self.generateFunction(func, cat)
                bufferHpp += self.generateDataReaderDeclaration(func, cat)
                bufferIDL += self.generateIDL(func, cat)
          
            idlfiles += idlfile

            mpcbuffer += self.generateLib(func, cat, idlfile, idlfileTypeSupport, readerImplHpp, readerImplCpp)
            mpcdatareaderbuffer += self.generateLibDataReader(func, cat, idlfile, idlfileTypeSupport, readerImplHpp, readerImplCpp)
            mpcdatareaderbufferNT += self.generateLibDataReaderNT(func, cat, idlfile, idlfileTypeSupport, readerImplHpp, readerImplCpp)

            print("Processing catalog : " + cat.name())

            self.bufferBody_.set({
                'bufferCpp' : bufferCpp,
		'qlAddinName' : qlAddinName,
		'categoryName' : cat.name(),
                'categoryIncludes' : categoryIncludes })

            self.bufferHeader_.set({
                'categoryName' : cat.name(),
                'bufferHpp' : bufferHpp,
                'qlAddinName' : qlAddinName,
                'categoryIncludes' : categoryIncludes })

            self.bufferModule_.set({
                'categoryName' : cat.name(),
                'bufferIdl' : bufferIDL })

            self.bufferMpc_.set({ 'mpcbuffer' : mpcbuffer })
            self.bufferMpcDataReader_.set({ 'mpcdatareaderbuffer' : mpcdatareaderbuffer })
            self.bufferMpcDataReaderNT_.set({ 'mpcdatareaderbuffer' : mpcdatareaderbufferNT })

            fileNameCpp = '%s%sDataReaderListenerImpl.cpp' % ( self.rootPath_, cat.name())
            outputfile.OutputFile(self, fileNameCpp, cat.copyright(), self.bufferBody_)

            fileNameHpp = '%s%sDataReaderListenerImpl.hpp' % ( self.rootPath_, cat.name())
            outputfile.OutputFile(self, fileNameHpp, cat.copyright(), self.bufferHeader_)

            fileNameIdl = '%s%s.idl' % ( self.rootPath_, cat.name())
            outputfile.OutputFile(self, fileNameIdl, cat.copyright(), self.bufferModule_)

            java_dir = '%s/java/%s' % ( self.rootPath_, cat.name() )
            if not os.path.exists(java_dir):
	      os.makedirs(java_dir)
   
            fileNameJavaIdl = '%s/%s.idl' % ( java_dir, cat.name() )
            outputfile.OutputFile( self, fileNameJavaIdl, cat.copyright(), self.bufferModule_ )
            
            mpcbufferJava = self.generateLibJava( cat.name(), cat.name() + ".idl" )
            self.bufferMpcJava_.set({ 'mpcbuffer' : mpcbufferJava })
            
            self.bufferMpcJava_.append("\n")
            fileNameMpcJava = '%s/QLDDS_Java_%s.mpc' % ( java_dir, cat.name() )
            outputfile.OutputFile( self, fileNameMpcJava, '', self.bufferMpcJava_ )

            mpc_java_path = '%s/QLDDS_Java_%s.mpc' % ( cat.name(), cat.name() )
            mwcbufferJava += mpc_java_path + '\n'
 

        self.bufferMpc_.append("\n")
        fileNameMpc = '%sQLDDS.mpc' % self.rootPath_
        outputfile.OutputFile(self, fileNameMpc, '', self.bufferMpc_)

        self.bufferMpcDataReader_.append("\n")
        fileNameMpc = '%sQLDDSDataReaders.mpc' % self.rootPath_
        outputfile.OutputFile(self, fileNameMpc, '', self.bufferMpcDataReader_)

        self.bufferMpcDataReaderNT_.append("\n")
        fileNameMpc = '%sQLDDSDataReaders_vc.mpc' % self.rootPath_
        outputfile.OutputFile(self, fileNameMpc, '', self.bufferMpcDataReaderNT_)

        self.bufferMwcJava_.set({'paths' : mwcbufferJava })
        self.bufferMwcJava_.append("\n")
        fileNameMwcJava = '%s/java/QLDDS_Java.mwc' % self.rootPath_
        outputfile.OutputFile(self, fileNameMwcJava, '', self.bufferMwcJava_ )      

    def generateFunction(self, func, cat):
        """Generate source code for a given function."""
        returnType =  self.functionReturnType_.apply(func.returnValue());
        qlCallResultDeclaration = ''
        qlCallResultType = '';
        returnStatement = ''
        libraryFunction = ''

        if returnType == "stringVector":
          qlCallResultType = 'std::vector<std::string>'
          qlCallResultDeclaration = qlCallResultType + ' returnObject;'
        elif returnType == "Property" :
          qlCallResultType = 'ObjectHandler::property_t'
          qlCallResultDeclaration = qlCallResultType + ' returnObject;'
        else : 
          if returnType == "String" :
            qlCallResultType = 'std::string'
            qlCallResultDeclaration = qlCallResultType + ' returnObject;'
          else:
            qlCallResultType = returnType; 
            qlCallResultDeclaration = qlCallResultType + ' returnObject;'

        return self.bufferDataReaderImplementation_.set({
            'functionDeclaration' : func.parameterList().generate(self.functionDeclaration_),
            'functionName' : func.name(),
            'functionReturnType' : self.functionReturnType_.apply(func.returnValue()),
            'categoryName' : cat.name(),
	    'qlCallResultDeclaration' : qlCallResultDeclaration, 
	    'libraryFunction' : libraryFunction,
            'qlCallResultType' : qlCallResultType
	 })

    def generateIDL(self, func, cat):
        """Generate idl code for a given function."""

        return self.bufferIDL_.set({
            'idlDeclaration' : func.parameterList().generate(self.idlDeclaration_),
            'functionName' : func.name(),
	    'categoryName': cat.name() })

    def generateLib(self, func, cat, idlfile, idlfileTypeSupport, readerImplHpp, readerImplCpp ):
        return self.bufferLib_.set({
            'libname' : cat.name(),
            'sharedname' : cat.name(),
	    'idlfile' : idlfile,
            'idlfileTypeSupport' : idlfileTypeSupport,
            'readerImplHpp' : readerImplHpp,
            'readerImplCpp' : readerImplCpp })

    def generateLibJava(self, libname, idlfile ) :
        return self.bufferLibJava_.set({
		'libname' : libname,
		'idlfile' : idlfile
		})

    def generateLibDataReader(self, func, cat, idlfile, idlfileTypeSupport, readerImplHpp, readerImplCpp ):
        return self.bufferLibDataReader_.set({
            'libname' : cat.name(),
            'sharedname' : cat.name(),
            'idlfile' : idlfile,
            'idlfileTypeSupport' : idlfileTypeSupport,
            'readerImplHpp' : readerImplHpp,
            'readerImplCpp' : readerImplCpp })

    def generateLibDataReaderNT(self, func, cat, idlfile, idlfileTypeSupport, readerImplHpp, readerImplCpp ):
        return self.bufferLibDataReaderNT_.set({
            'libname' : cat.name(),
            'sharedname' : cat.name(),
            'idlfile' : idlfile,
            'idlfileTypeSupport' : idlfileTypeSupport,
            'readerImplHpp' : readerImplHpp,
            'readerImplCpp' : readerImplCpp })

    def generateDataReaderDeclaration(self, func, cat):
        returnType =  self.functionReturnType_.apply(func.returnValue());

        if returnType == "stringVector":
          qlCallResultType = 'std::vector<std::string>'
          qlCallResultDeclaration = qlCallResultType + ' returnObject;'
        elif returnType == "Property" :
          qlCallResultType = 'ObjectHandler::property_t'
          qlCallResultDeclaration = qlCallResultType + ' returnObject;'
        else :
          if returnType == "String" :
            qlCallResultType = 'std::string'
            qlCallResultDeclaration = qlCallResultType + ' returnObject;'
          else:
            qlCallResultType = returnType;
            qlCallResultDeclaration = qlCallResultType + ' returnObject;'
   
        """Generate source code for a given function."""
        return self.bufferDataReaderDeclaration_.set({
            'functionDeclaration' : func.parameterList().generate(self.functionDeclaration_),
            'functionName' : func.name(),
	    'categoryName': cat.name(),
            'qlCallResultType' : qlCallResultType,  
            'functionReturnType' : self.functionReturnType_.apply(func.returnValue()) })

    #############################################
    # serializer interface
    #############################################

    def serialize(self, serializer):
        """Load/unload class state to/from serializer object."""
        super(OpenDDSAddin, self).serialize(serializer)
