
/*
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
*/


#include <BasicDomainParticipant.h>
#include <NamingServiceUtils.h>

#include <ql/quantlib.hpp>
#include <oh/ohdefines.hpp>
#include <Addins/Cpp/addincpp.hpp>

#include <ratehelpersTypeSupportImpl.h>
#include <swaptionvolstructureTypeSupportImpl.h>

#include <ratehelpersDataReaderListenerImpl.hpp>
#include <swaptionvolstructureDataReaderListenerImpl.hpp>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <ace/Get_Opt.h>

#include "SwaptionServerImpl.h"

#include <qldds_convert_utils.h>

#include "Common.h"

ACE_Mutex qldds_lock;

class DepositRateHelper2DataReaderListenerImpl : 
     public ratehelpers::qlDepositRateHelper2DataReaderListenerImpl
{
  public:

    DepositRateHelper2DataReaderListenerImpl( ACE_Mutex& mutex ) : 
      ratehelpers::qlDepositRateHelper2DataReaderListenerImpl( mutex ) {};

    virtual bool pre_quantlib_addin_call
       ( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlDepositRateHelper2 & deposit_rate_helper2 )
    {
      ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

      std::vector<std::string> objects(1);
      objects[0] = deposit_rate_helper2.ObjectId;  
   
      std::vector<bool> existing_curve_object = ObjectHandler::Repository::instance().objectExists( objects );
      if ( existing_curve_object[0] == true )
        ObjectHandler::Repository::instance().deleteObject( objects[0] );
 
      return true;
    }
};

class FraRateHelper2DataReaderListenerImpl :
   public ratehelpers::qlFraRateHelper2DataReaderListenerImpl
{
  public:

    FraRateHelper2DataReaderListenerImpl( ACE_Mutex& mutex ) :
      ratehelpers::qlFraRateHelper2DataReaderListenerImpl( mutex ) {};

    virtual bool pre_quantlib_addin_call
       ( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFraRateHelper2 & fra_rate_helper2 )
    {
      ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

      std::vector<std::string> objects(1);
      objects[0] = fra_rate_helper2.ObjectId;
  
      std::vector<bool> existing_curve_object = ObjectHandler::Repository::instance().objectExists( objects );
      if ( existing_curve_object[0] == true )
        ObjectHandler::Repository::instance().deleteObject( objects[0] );

      return true;
    }
};

class SwapRateHelper2DataReaderListenerImpl : 
   public ratehelpers::qlSwapRateHelper2DataReaderListenerImpl
{
  public:

    SwapRateHelper2DataReaderListenerImpl( ACE_Mutex& mutex ) :
      ratehelpers::qlSwapRateHelper2DataReaderListenerImpl ( mutex ) {};

    virtual bool pre_quantlib_addin_call
       ( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlSwapRateHelper2 & swap_rate_helper2 )
    {

      ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

      std::vector<std::string> objects(1);
      objects[0] = swap_rate_helper2.ObjectId;

 
      std::vector<bool> existing_curve_object = ObjectHandler::Repository::instance().objectExists( objects );
      if ( existing_curve_object[0] == true )
        ObjectHandler::Repository::instance().deleteObject( objects[0] );

      return true;
    }

};


int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try
  {
     QuantLibAddinCpp::initializeAddin();

     QuantLib::Calendar calendar = QuantLib::TARGET();

     QuantLib::Date settlementDate(22, QuantLib::September, 2004);

     settlementDate = calendar.adjust(settlementDate);

     QuantLib::Integer fixingDays = 2;

     QuantLib::Date todaysDate = calendar.advance(settlementDate, -fixingDays, QuantLib::Days);

     QuantLibAddinCpp::qlSettingsSetEvaluationDate( todaysDate.serialNumber(), OH_NULL );
     std::cout << "Today: " << todaysDate.weekday() << ", " << todaysDate << std::endl;
     std::cout << "Settlement date: " << settlementDate.weekday() << ", " << settlementDate << std::endl;

     CORBA::ORB_var swaptionServerORB = CORBA::ORB_init(argc, argv, "SwaptionServerORB");

      // Initialize, and create a DomainParticipant
     dpf = TheParticipantFactoryWithArgs(argc, argv);

     std::string server_name;
     ACE_Get_Opt cmd_opts( argc, argv, ":s:" );
     int option;

     while ( (option = cmd_opts()) != EOF )
     {
      switch( option )
      {
        case 's' :
          server_name = cmd_opts.opt_arg();
          std::cout << "ServerName: " << server_name << std::endl;
        break;
      }
     }

     qldds_utils::BasicDomainParticipant swaptionServer( dpf, SWAPTION_DOMAIN_ID );
     swaptionServer.createSubscriber();

     QuantLibAddinCpp::qlLibor("Libor", "USD", "6M", "", false, false, true);
     
     // Topics for curve components
     // setting up deposit rate helper
     DDS::Topic_var topic_deposit_rate_helper2 = swaptionServer.createTopicAndRegisterType
         < ratehelpers::qlDepositRateHelper2TypeSupport_var, ratehelpers::qlDepositRateHelper2TypeSupportImpl >
          ( DEPOSIT_RATE_HELPER2_TOPIC_NAME );

     // setting up FRA Rate helper
     DDS::Topic_var topic_fra_rate_helper2 = swaptionServer.createTopicAndRegisterType
         < ratehelpers::qlFraRateHelper2TypeSupport_var, ratehelpers::qlFraRateHelper2TypeSupportImpl >
          ( FRA_RATE_HELPER2_TOPIC_NAME );

     // setting up Swap Rate helper
     DDS::Topic_var topic_swap_rate_helper2 = swaptionServer.createTopicAndRegisterType
       < ratehelpers::qlSwapRateHelper2TypeSupport_var, ratehelpers::qlSwapRateHelper2TypeSupportImpl >
        ( SWAP_RATE_HELPER2_TOPIC_NAME );

     // setting up Swaption VTS Matrix
     DDS::Topic_var topic_swaption_vts_matrix = swaptionServer.createTopicAndRegisterType
       < swaptionvolstructure::qlSwaptionVTSMatrixTypeSupport_var, swaptionvolstructure::qlSwaptionVTSMatrixTypeSupportImpl >
        ( SWAPTION_VTS_MATRIX_TOPIC_NAME );


    swaptionServer.createDataReaderListener< DepositRateHelper2DataReaderListenerImpl > ( qldds_lock, topic_deposit_rate_helper2 );
    swaptionServer.createDataReaderListener< FraRateHelper2DataReaderListenerImpl > ( qldds_lock, topic_fra_rate_helper2 );
    swaptionServer.createDataReaderListener< SwapRateHelper2DataReaderListenerImpl > ( qldds_lock, topic_swap_rate_helper2 );
    swaptionServer.createDataReaderListener< swaptionvolstructure::qlSwaptionVTSMatrixDataReaderListenerImpl > 
         ( qldds_lock, topic_swaption_vts_matrix );

    std::vector<ObjectHandler::property_t> fixingDates(1);
    fixingDates[0] = qldds_utils::from_iso_string_to_oh_property("20040916");


    std::vector<double> fixingValues(1);
    fixingValues[0] = 0.05;

   QuantLibAddinCpp::qlIndexAddFixings("Libor", fixingDates, fixingValues, false, false);

    
    // SwapServerORB POA
    CORBA::Object_var obj = swaptionServerORB->resolve_initial_references( "RootPOA" );
    PortableServer::POA_var poa = PortableServer::POA::_narrow( obj.in() );

    // Activate POA Manager
    PortableServer::POAManager_var mgr = poa->the_POAManager();
    mgr->activate();

    qldds_utils::NamingService::Server< SwaptionServerImpl > server( qldds_lock );

    server.Init( swaptionServerORB, server_name.c_str() );

    ACE_Time_Value time_out(20);

    swaptionServerORB->run( time_out );

    swaptionServerORB->destroy();

  } catch (CORBA::Exception& e)
  {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown();

  return 0;
}
