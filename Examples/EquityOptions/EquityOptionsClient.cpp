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

#include "StraddlesTypeSupportImpl.h"

class StraddlesDataReaderListenerImpl;

typedef struct {
  Option put;
  Option call;
} SingleStikeStraddle;


std::vector< std::string > headers(11);

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try {

    dpf = TheParticipantFactoryWithArgs(argc, argv);

    qldds_utils::BasicDomainParticipant participant( dpf, EQUITY_OPTIONS_DOMAIN_ID );
    participant.createSubscriber();
    participant.createPublisher();

    headers[0] = "Vega";
    headers[1] = "Gamma";
    headers[2] = "Delta";
    headers[3] = "Vol %";
    headers[4] = "NPV";
    headers[5] = "Strike";
    headers[6] = "NPV";
    headers[7] = "Vol %";
    headers[8] = "Delta";
    headers[9] = "Gamma";
    headers[10] = "Vega";

    // Setting up Equity Options Straddles Topic
    DDS::Topic_var straddles_topic = participant.createTopicAndRegisterType
      < StraddlesTypeSupport_var, StraddlesTypeSupportImpl >
       ( STRADDLES_TOPIC_NAME );

    participant.createDataReaderListener< StraddlesDataReaderListenerImpl > ( straddles_topic );

    // Run for 30 seconds
    for ( int tt = 0; tt<30; tt++ )
    {
      ACE_OS::sleep(1);
    }

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


class StraddlesDataReaderListenerImpl 
    : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
{
  public:
    virtual void on_data_available( DDS::DataReader_ptr reader)
      throw (CORBA::SystemException)
    {
      try
      {
        StraddlesDataReader_var straddles_dr = StraddlesDataReader::_narrow(reader);
        if (CORBA::is_nil ( straddles_dr.in() ) )
        {
          std::cerr << "StraddlesDataReaderListenerImpl::on_data_available: _narrow failed." << std::endl;
          ACE_OS::exit(1);
        }

        while( true )
        {
          Straddles straddles;
          DDS::SampleInfo si ;
          DDS::ReturnCode_t status = straddles_dr->take_next_sample( straddles, si );

          if (status == DDS::RETCODE_OK && si.valid_data == true )
          {
             std::map< int, SingleStikeStraddle > straddleView;

             for ( long opt = 0; opt<straddles.options.length(); opt++ )
             {
               Option option = straddles.options[ opt ];

               int strike = static_cast<int>( option.strike * 1000 );
              
               std::map< int, SingleStikeStraddle >::iterator iter;  

               if ( ( iter = straddleView.find( strike ) ) != straddleView.end() )
               {
                 if ( PUT == option.option_type.in() )
                   iter->second.put = option;
                 else
                   iter->second.call = option;
                
               } else {

                 SingleStikeStraddle singleStrikeStraddle;
                  
                 if ( PUT == option.option_type.in() )
                   singleStrikeStraddle.put = option;
                 else
                   singleStrikeStraddle.call = option;

                 straddleView.insert( std::pair< int, SingleStikeStraddle > ( strike, singleStrikeStraddle ) );

               }
             }

             std::map< int, SingleStikeStraddle >::iterator iter;  

             std::string rule( 76,'-' );
             std::string tab( 8, ' ' );

             std::cout << "|" << rule << "|" << std::endl;
             std::cout << std::setw( 20 )  
                       << tab << "Symbol : " << straddles.ticker << tab
                       << tab << "Price : " << straddles.underlying << std::endl; 

             std::cout << "|" << rule << "|" << std::endl << "|";

             std::cout << std::setw( 20 ) << tab << "Puts" << tab << tab << tab << "Calls" << std::endl;

             std::cout << "|" << rule << "|" << std::endl << "|";

             for( int header = 0; header < headers.size(); header++ )
               std::cout << std::setw(6) << headers[ header ] << "|";

             std::cout << std::endl << "|"<< rule << "|" << std::endl;

             for ( iter = straddleView.begin(); iter != straddleView.end(); iter++ )
             {
               std::cout << "|" << std::setprecision(5) 
                         << std::setw(6) << iter->second.put.vega << "|"
                         << std::setw(6) << iter->second.put.gamma << "|"
                         << std::setw(6) << iter->second.put.delta << "|"
                         << std::setw(6) << iter->second.put.volatility * 100 << "|"
                         << std::setw(6) << iter->second.put.npv << "|"
                         << std::setw(6) << static_cast<double>(iter->first/1000.0) << "|" 
                         << std::setw(6) << iter->second.call.npv << "|" 
                         << std::setw(6) << iter->second.call.volatility * 100 << "|"
                         << std::setw(6) << iter->second.call.delta << "|"
                         << std::setw(6) << iter->second.call.gamma << "|"
                         << std::setw(6) << iter->second.call.vega << "|"
                         << std::endl; 
             }

             std::cout << "|" << rule << "|" << std::endl;

           } else if (status == DDS::RETCODE_NO_DATA || si.valid_data == false ) {
                 break;
           } else {
                std::cerr << "ERROR: read Straddles: Error: " <<  status << std::endl;
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
