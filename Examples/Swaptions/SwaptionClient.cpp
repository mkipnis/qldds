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
#include <ace/Get_Opt.h>

#include "SwaptionsC.h"
#include "SwaptionsTypeSupportC.h"
#include "SwaptionsTypeSupportImpl.h"

#include "Common.h"

#include <map>

std::map<long, swaptions::SwaptionPriceRequest> swaptionPriceRequestMap;

class SwaptionPriceReplyDataReaderListenerImpl : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
{
  public:
        virtual void on_data_available( DDS::DataReader_ptr reader) throw (CORBA::SystemException)
        {
            swaptions::SwaptionPriceReplyDataReader_var swaption_price_reply_dr = swaptions::SwaptionPriceReplyDataReader::_narrow(reader);
            if (CORBA::is_nil ( swaption_price_reply_dr.in() ) )
            {
              std::cerr << "SwaptionPriceReplyDataReaderListenerImpl::on_data_available: _narrow failed." << std::endl;
              ACE_OS::exit(1);
            }

            while( true )
            {
               swaptions::SwaptionPriceReply swaption_price_reply;
               DDS::SampleInfo si ;
               DDS::ReturnCode_t status = swaption_price_reply_dr->take_next_sample( swaption_price_reply, si );

               if (status == DDS::RETCODE_OK)
               {
                 if ( !si.valid_data )
                   continue;

		std::map<long, swaptions::SwaptionPriceRequest>::iterator request_iter = swaptionPriceRequestMap.find( swaption_price_reply.request_id );

		if ( request_iter != swaptionPriceRequestMap.end() )
		{
			std::cout << "Swaption Price : " <<  swaption_price_reply.request_id << "|" << swaption_price_reply.calculator_name <<  "|" << swaption_price_reply.rate << "|" << swaption_price_reply.npv  << "|" << swaption_price_reply.error << std::endl;

			swaptionPriceRequestMap.erase( request_iter );
		}
		} else if (status == DDS::RETCODE_NO_DATA) {
                 break;
               } else {
                 std::cerr << "ERROR: read IRS::Portfolio: Error: " <<  status << std::endl;
               }

		}


	}

	
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
  try {

    DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
    DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();


    // Initialize, and create a DomainParticipant
    dpf = TheParticipantFactoryWithArgs(argc, argv);

    qldds_utils::BasicDomainParticipant clientParticipant( dpf, SWAPTION_DOMAIN_ID );
    clientParticipant.createPublisher();
    clientParticipant.createSubscriber();

    ACE_Get_Opt cmd_opts( argc, argv, ":c:" ); 

    int option;
    
    std::vector<std::string> curve_components;

    while ( (option = cmd_opts()) != EOF )
    {
      switch( option )
      { 
        case 'c' :

         std::istringstream f( cmd_opts.opt_arg() );
         std::string s;

         while (std::getline(f, s, '|')) {
           curve_components.push_back(s);
         }

        break;
      }
    } 

     DDS::Topic_var topic_swaption_price_request = clientParticipant.createTopicAndRegisterType
       < swaptions::SwaptionPriceRequestTypeSupport_var, swaptions::SwaptionPriceRequestTypeSupportImpl >
        ( SWAPTION_PRICE_REQUEST_TOPIC_NAME );

     DDS::Topic_var topic_swaption_price_reply = clientParticipant.createTopicAndRegisterType
       < swaptions::SwaptionPriceReplyTypeSupport_var, swaptions::SwaptionPriceReplyTypeSupportImpl >
        ( SWAPTION_PRICE_REPLY_TOPIC_NAME );

     swaptions::SwaptionPriceRequestDataWriter_var swaption_request_dw = clientParticipant.createDataWriter
      < swaptions::SwaptionPriceRequestDataWriter_var, swaptions::SwaptionPriceRequestDataWriter >
       ( topic_swaption_price_request );

     clientParticipant.createDataReaderListener<SwaptionPriceReplyDataReaderListenerImpl> ( topic_swaption_price_reply );



    CORBA::StringSeq curve;
    curve.length( curve_components.size() );

    // Copy curve from std::vector to CORBA string array
    for ( int cc = 0; cc < curve_components.size(); cc++ )
    {
       std::cout <<  curve_components[cc] << std::endl;
       curve[cc] = CORBA::string_dup( curve_components[cc].c_str() );
    }

    long request_id = 0;

    for ( int tt = 0; tt<10; tt++ )
    {
      swaptions::SwaptionPriceRequest spr;
      CORBA::Double npv;
      CORBA::Double rate;
      CORBA::String_var error;

      spr.curve_components = curve;

      spr.surface_name = CORBA::string_dup( "SwaptionVTSMatrix" );
 
      for ( int month = 1; month<=12; month++ )
      {
        for ( int year = 1; year<=15; year++ )
        {
          std::stringstream swaption_tenor;
          swaption_tenor << month << "M";

          std::stringstream swap_tenor;
          swap_tenor << year << "Y";

	  spr.request_id = request_id++;
          spr.swaption_tenor = CORBA::string_dup( swaption_tenor.str().c_str() );
          spr.swap_tenor = CORBA::string_dup( swap_tenor.str().c_str() );

 	 int ret = swaption_request_dw->write( spr, DDS::HANDLE_NIL );
    	 if (ret != DDS::RETCODE_OK) {
         	ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Swaptions Price Request Write Returned %d.\n"), ret));
      	 }

	 swaptionPriceRequestMap.insert( std::pair<long,  swaptions::SwaptionPriceRequest>(request_id, spr) );

        }
      }
    } 

    while ( 1 )
    {
      ACE_OS::sleep(1);
    }

  } catch (CORBA::Exception& e) {
    e._tao_print_exception("CORBA Exception caught in main():");
    return 0;
  } catch (...)
  {
    std::cerr << "Exception caught in main():" << std::endl;
    return 0;
  }

  TheServiceParticipant->shutdown(); 

  return 0;
}
