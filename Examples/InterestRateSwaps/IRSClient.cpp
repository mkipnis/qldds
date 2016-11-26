
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

#include "Common.h"

#include "IRSPortfolioTypeSupportImpl.h"

class IRSPortfolioDataReaderListenerImpl;

std::string client_id;

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try {

    dpf = TheParticipantFactoryWithArgs(argc, argv);

    qldds_utils::BasicDomainParticipant participant( dpf, IRS_DOMAIN_ID );
    participant.createSubscriber();
    participant.createPublisher();

    ACE_Get_Opt cmd_opts( argc, argv, ":i:" );

    int option;

    while ( (option = cmd_opts()) != EOF )
    {
      switch( option )
      {
        case 'i' :
         client_id = cmd_opts.opt_arg();
        break;
      }
    }

    // Setting up IRS Portfolio Topic 
    DDS::Topic_var irs_portfolio_topic = participant.createTopicAndRegisterType
      < IRS::PortfolioTypeSupport_var, IRS::PortfolioTypeSupportImpl >
       ( IRS_PORTFOLIO_TOPIC_NAME );

    participant.createDataReaderListener< IRSPortfolioDataReaderListenerImpl > ( irs_portfolio_topic );

    // Keep the client up for 30 seconds
    for ( int times=0; times<30; times++)
      ACE_OS::sleep(1);

  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  } catch ( std::exception& exp )
  {
    cerr << "Exception caught in main.cpp:" << endl << exp.what() << endl;
  }

  TheServiceParticipant->shutdown ();

  return 0;
}


class IRSPortfolioDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
  {
    public:
      virtual void on_data_available( DDS::DataReader_ptr reader)
        throw (CORBA::SystemException) 
        {
           try 
           {
             IRS::PortfolioDataReader_var irs_portfolio_dr = IRS::PortfolioDataReader::_narrow(reader);
             if (CORBA::is_nil ( irs_portfolio_dr.in() ) ) 
             {
               std::cerr << "IRS::PortfolioDataReaderListenerImpl::on_data_available: _narrow failed." << std::endl;
               ACE_OS::exit(1);
             }

             while( true ) 
             {
               IRS::Portfolio irs_portfolio;
               DDS::SampleInfo si ;
               DDS::ReturnCode_t status = irs_portfolio_dr->take_next_sample( irs_portfolio, si );

               if (status == DDS::RETCODE_OK) 
               {
                 if ( !si.valid_data ) 
                   continue;

                 double npv = 0.0;
                 
                 for ( long swap = 0; swap<irs_portfolio.swaps.length(); swap++ )
                 {
                   npv += irs_portfolio.swaps[swap].npv;
                 }

                 std::string separator = " | ";

                 std::cout << std::setw(10) << client_id << separator;
                 std::cout << std::setw(20) << irs_portfolio.term_structure.in() << separator;
                 std::cout << std::setw(10) << "Swaps=" << irs_portfolio.swaps.length() << separator;
                 std::cout << std::setw(10) << "NPV=" << npv << separator;
                 std::cout << std::endl; 

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

