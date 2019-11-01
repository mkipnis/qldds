/*
   Copyright (C) 2013 Mike Kipnis

   This file is part of QLDDS, a free-software/open-source library
   for utilization of QuantLib in the distributed envrionment via DDS.

   QLDDS is free software: you can redistribute it and/or modify it
   under the terms of the QLDDS license.  You should have received a
   copy of the license along with this program; if not, please email
   <dev@qldds.org>. The license is also available online at
   <http://qldds.org/qldds-license/>.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the license for more details.
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

#include "SwaptionsC.h"
#include "SwaptionsTypeSupportC.h"
#include "SwaptionsTypeSupportImpl.h"

#include <vector>
#include <oh/repository.hpp>
#include <ql/quantlib.hpp>

#include <Addins/Cpp/addincpp.hpp>

#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/indexes/swap/liborswap.hpp>
#include <qlo/swaption.hpp>
#include <qlo/vanillaswap.hpp>


#include "Common.h"

ACE_Mutex qldds_lock;

using namespace QuantLibAddinCpp;


std::string server_name;

ObjectHandler::property_t ATM_RATE;

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


class SwaptionPriceRequestDataReaderListenerImpl : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
{
     private:
	swaptions::SwaptionPriceReplyDataWriter_var _swaption_price_reply_dw;
     public:


	SwaptionPriceRequestDataReaderListenerImpl( swaptions::SwaptionPriceReplyDataWriter_var& swaption_price_reply_dw ) : _swaption_price_reply_dw( swaption_price_reply_dw  )
	{
	};

        virtual void on_data_available( DDS::DataReader_ptr reader)
        throw (CORBA::SystemException)
        {
           try
           {
             swaptions::SwaptionPriceRequestDataReader_var swaption_price_request_dr = swaptions::SwaptionPriceRequestDataReader::_narrow(reader);
             if (CORBA::is_nil ( swaption_price_request_dr.in() ) )
             {
               std::cerr << "SwaptionPriceRequestDataReaderListenerImpl::on_data_available: _narrow failed." << std::endl;
               ACE_OS::exit(1);
             }

             while( true )
             {
               swaptions::SwaptionPriceRequest swaption_price_request;
               DDS::SampleInfo si ;
               DDS::ReturnCode_t status = swaption_price_request_dr->take_next_sample( swaption_price_request, si );

               if (status == DDS::RETCODE_OK)
               {
                 if ( !si.valid_data )
                   continue;

	/*	std::cout << "Recieved Swaption Price Request : " 
				<< swaption_price_request.request_id 
				<< "|" << swaption_price_request.surface_name 
				<< "|" << swaption_price_request.swaption_tenor 
				<< "|" << swaption_price_request.swap_tenor << std::endl; */

		ACE_Guard<ACE_Mutex> guard( qldds_lock );

		ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) INFO: ") ACE_TEXT("SwaptionPriceRequestDataReaderListenerImpl CalculatingATM - %s%s\n"),
			 swaption_price_request.swaption_tenor.in(), swaption_price_request.swap_tenor.in() ));

		std::vector< std::string > curve( swaption_price_request.curve_components.length() );

		for ( unsigned int tt = 0; tt < swaption_price_request.curve_components.length(); tt++ )
			curve[tt] = swaption_price_request.curve_components[tt];

		std::vector<bool> existing_objects = ObjectHandler::Repository::instance().objectExists( curve );

		for ( unsigned int rate_helper = 0; rate_helper < curve.size(); rate_helper++ )
		{
			if ( !existing_objects[ rate_helper ] )
			{
				std::cout << "Rate Helper : [" << curve[ rate_helper ] << "] hasn't been setup yet." << std::endl;
				continue;
			}
		}

		QuantLib::Date referenceDate = QuantLib::Settings::instance().evaluationDate();

		swaptions::SwaptionPriceReply reply;

		try
		{

			std::vector<ObjectHandler::property_t> jumps;
			std::vector< std::string > curve1;

			QuantLibAddinCpp::qlPiecewiseYieldCurve( "PiecewiseYieldCurve", static_cast<long>(2), "Target", curve,
				 "Actual/Actual (ISDA)", jumps, jumps, 1.0e-15, "Discount", "LogLinear", OH_NULL, OH_NULL, true);

			std::string engine = QuantLibAddinCpp::qlBlackSwaptionEngine( "blackSwaptionEngine", "PiecewiseYieldCurve", swaption_price_request.surface_name.in(), OH_NULL, OH_NULL, true);

			std::string liborSwapIndexIsdaFixAm = QuantLibAddinCpp::qlLiborSwap( "LiborSwapIsdaFixAm", "USD", "IsdaFixAm", swaption_price_request.swap_tenor.in(),
				 "PiecewiseYieldCurve", "PiecewiseYieldCurve", OH_NULL, OH_NULL, true);

			std::string swaption = QuantLibAddinCpp::qlMakeSwaption( "Swaption555", "LiborSwapIsdaFixAm", swaption_price_request.swaption_tenor.in(), ATM_RATE,
				 "blackSwaptionEngine", OH_NULL, OH_NULL, true);

			OH_GET_REFERENCE(ObjectIdLibObjPtr, swaption, QuantLibAddin::Swaption, QuantLib::Swaption)

			reply.calculator_name = server_name.c_str();

			reply.request_id = swaption_price_request.request_id;

			reply.rate = ObjectIdLibObjPtr->underlyingSwap()->fairRate();

			reply.npv = ObjectIdLibObjPtr->NPV();

		} catch ( std::exception& exp )
		{
			std::cout << "Exception : " << exp.what() << std::endl;
			reply.error = CORBA::string_dup( exp.what() );
		}

		//std::cout << "Swaption Price : " <<  reply.request_id <<  "|" << reply.rate << "|" << reply.npv << std::endl;
		//
		//	

		int ret = _swaption_price_reply_dw->write( reply, DDS::HANDLE_NIL );

	        if (ret != DDS::RETCODE_OK) {
         	        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Swaptions Price Reply Write Returned %d.\n"), ret));
         	}


               } else if (status == DDS::RETCODE_NO_DATA) {
                 break;
               } else {
                 std::cerr << "ERROR: read IRS::Portfolio: Error: " <<  status << std::endl;
               }
             }

           } catch (CORBA::Exception& e) {
             std::cerr << "Exception caught in read:" << std::endl << e << std::endl;
             ACE_OS::exit(1);
           }
        };

     virtual void on_requested_deadline_missed ( DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status)
        throw (CORBA::SystemException) {};

      virtual void on_requested_incompatible_qos ( DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status)
        throw (CORBA::SystemException) {};

      virtual void on_liveliness_changed ( DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status)
        throw (CORBA::SystemException) {};

      virtual void on_subscription_matched ( DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status)
        throw (CORBA::SystemException) {};

      virtual void on_sample_rejected( DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status)
        throw (CORBA::SystemException) {};

      virtual void on_sample_lost( DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status)
        throw (CORBA::SystemException) {};

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

      // Initialize, and create a DomainParticipant
     dpf = TheParticipantFactoryWithArgs(argc, argv);

     qldds_utils::BasicDomainParticipant swaptionServer( dpf, SWAPTION_DOMAIN_ID );
     swaptionServer.createSubscriber();
     swaptionServer.createPublisher();

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

     DDS::Topic_var topic_swaption_price_request = swaptionServer.createTopicAndRegisterType
       < swaptions::SwaptionPriceRequestTypeSupport_var, swaptions::SwaptionPriceRequestTypeSupportImpl >
	( SWAPTION_PRICE_REQUEST_TOPIC_NAME );

     DDS::Topic_var topic_swaption_price_reply = swaptionServer.createTopicAndRegisterType
       < swaptions::SwaptionPriceReplyTypeSupport_var, swaptions::SwaptionPriceReplyTypeSupportImpl >
	( SWAPTION_PRICE_REPLY_TOPIC_NAME );

    
     swaptions::SwaptionPriceReplyDataWriter_var swaption_price_reply_dw = swaptionServer.createDataWriter
      < swaptions::SwaptionPriceReplyDataWriter_var, swaptions::SwaptionPriceReplyDataWriter >
       ( topic_swaption_price_reply );



    swaptionServer.createDataReaderListener< DepositRateHelper2DataReaderListenerImpl > ( qldds_lock, topic_deposit_rate_helper2 );
    swaptionServer.createDataReaderListener< FraRateHelper2DataReaderListenerImpl > ( qldds_lock, topic_fra_rate_helper2 );
    swaptionServer.createDataReaderListener< SwapRateHelper2DataReaderListenerImpl > ( qldds_lock, topic_swap_rate_helper2 );
    swaptionServer.createDataReaderListener< swaptionvolstructure::qlSwaptionVTSMatrixDataReaderListenerImpl > 
         ( qldds_lock, topic_swaption_vts_matrix );

    DDS::DataReaderListener_var swaptionPriceRequestDataReaderListenerImpl (new SwaptionPriceRequestDataReaderListenerImpl( swaption_price_reply_dw ) );

    swaptionServer.createDataReaderListener ( topic_swaption_price_request, swaptionPriceRequestDataReaderListenerImpl );

    std::vector<ObjectHandler::property_t> fixingDates(1);
    fixingDates[0] = qldds_utils::from_iso_string_to_oh_property("2004-09-16");

    std::vector<double> fixingValues(1);
    fixingValues[0] = 0.05;

   QuantLibAddinCpp::qlIndexAddFixings("Libor", fixingDates, fixingValues, false, false);

   while ( 1 )
   {
     ACE_OS::sleep(1);
   } 

  } catch (CORBA::Exception& e)
  {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown();

  return 0;
}
