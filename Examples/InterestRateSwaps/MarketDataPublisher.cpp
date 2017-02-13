

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
#include <ratehelpersTypeSupportImpl.h>

#include "Common.h"

#include <math.h>

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try {

    dpf = TheParticipantFactoryWithArgs(argc, argv);

    qldds_utils::BasicDomainParticipant participant( dpf, IRS_DOMAIN_ID );
    participant.createPublisher();

    // Topics
    // setting up deposit rate helper
    DDS::Topic_var deposit_rate_helper2_topic = participant.createTopicAndRegisterType
        < ratehelpers::qlDepositRateHelper2TypeSupport_var, ratehelpers::qlDepositRateHelper2TypeSupportImpl >
         ( DEPOSIT_RATE_HELPER2_TOPIC_NAME );

    // setting up FRA Rate helper
    DDS::Topic_var fra_rate_helper2_topic = participant.createTopicAndRegisterType
        < ratehelpers::qlFraRateHelper2TypeSupport_var, ratehelpers::qlFraRateHelper2TypeSupportImpl >
         ( FRA_RATE_HELPER2_TOPIC_NAME );

    // setting up Swap Rate helper
    DDS::Topic_var swap_rate_helper2_topic = participant.createTopicAndRegisterType
      < ratehelpers::qlSwapRateHelper2TypeSupport_var, ratehelpers::qlSwapRateHelper2TypeSupportImpl >
       (  SWAP_RATE_HELPER2_TOPIC_NAME );

    //  Data Writers
   ratehelpers::qlDepositRateHelper2DataWriter_var deposit_rate_helper2_dw = participant.createDataWriter
      < ratehelpers::qlDepositRateHelper2DataWriter_var, ratehelpers::qlDepositRateHelper2DataWriter >
       ( deposit_rate_helper2_topic );

    ratehelpers::qlFraRateHelper2DataWriter_var fra_rate_helper2_dw = participant.createDataWriter
      < ratehelpers::qlFraRateHelper2DataWriter_var, ratehelpers::qlFraRateHelper2DataWriter >
       ( fra_rate_helper2_topic );

    ratehelpers::qlSwapRateHelper2DataWriter_var swap_rate_helper2_dw = participant.createDataWriter
      < ratehelpers::qlSwapRateHelper2DataWriter_var, ratehelpers::qlSwapRateHelper2DataWriter >
       ( swap_rate_helper2_topic );


    ratehelpers::qlDepositRateHelper2 deposit_rate_helper2;
    DDS::InstanceHandle_t deposit_rate_helper2_instance = 
      deposit_rate_helper2_dw->register_instance( deposit_rate_helper2 );

    ratehelpers::qlFraRateHelper2 fra_rate_helper2;
    DDS::InstanceHandle_t fra_rate_helper2_instance = fra_rate_helper2_dw->register_instance( fra_rate_helper2 );

    ratehelpers::qlSwapRateHelper2 swap_rate_helper2;
    DDS::InstanceHandle_t swap_rate_helper2_instance = swap_rate_helper2_dw->register_instance( swap_rate_helper2 );

    CORBA::Double deposit_rates[] = {
      0.0082,
      0.01,
      0.012,
      0.013,
      0.014,
      0.015
    };

    CORBA::String_var deposit_tenors[] = {
      "1W",
      "1M",
      "3M",
      "6M",
      "9M",
      "1Y"
    };

    // Deposit Rate Indicatives
    deposit_rate_helper2.FixingDays = 2;
    deposit_rate_helper2.Convention = CORBA::string_dup("Modified Following");
    deposit_rate_helper2.EndOfMonth = true;
    deposit_rate_helper2.Calendar = CORBA::string_dup("TARGET");
    deposit_rate_helper2.DayCounter = CORBA::string_dup("A/365 (Fixed)");
    deposit_rate_helper2.Overwrite = true;


    CORBA::String_var fra_periods_to_start[] = {
      "3M",
      "6M",
      "6M"
    };

    CORBA::Long fra_lenghts_in_months[] = {
      6,
      9,
      12
    };


    CORBA::Double fra_rates[] = {
      0.017125,
      0.017125,
      0.017125
    };

    // FRA indicatives
    fra_rate_helper2.FixingDays = 2;
    fra_rate_helper2.Convention = CORBA::string_dup("Modified Following");
    fra_rate_helper2.EndOfMonth = true;
    fra_rate_helper2.Calendar = CORBA::string_dup("TARGET");
    fra_rate_helper2.DayCounter = CORBA::string_dup("A/365 (Fixed)");
    fra_rate_helper2.Overwrite = true;
    fra_rate_helper2.PillarDate = CORBA::string_dup("LastRelevantDate");

    CORBA::Double swap_rates[] = {
      0.017125,
      0.0198,
      0.0243,
      0.03165,
      0.03175,
      0.045
    };

    CORBA::String_var swap_tenors[] = {
      "2Y",
      "3Y",
      "5Y",
      "10Y",
      "15Y",
      "50Y"
    };

    swap_rate_helper2.SettlDays = 2;
    swap_rate_helper2.Calendar = CORBA::string_dup("TARGET");
    swap_rate_helper2.FixedLegFrequency = CORBA::string_dup("Annual");
    swap_rate_helper2.FixedLegConvention = CORBA::string_dup("Unadjusted");
    swap_rate_helper2.FixedLegDayCounter = CORBA::string_dup("30/360");
    swap_rate_helper2.IborIndex =  CORBA::string_dup("Libor");
    swap_rate_helper2.ForwardStart =  CORBA::string_dup("0D");
    swap_rate_helper2.Spread = 0.0;
    swap_rate_helper2.PillarDate = CORBA::string_dup("LastRelevantDate");
    swap_rate_helper2.Overwrite = true;

    
    // 
    // Market data will be published for 30 seconds at the rate of 4 updates a second
    // 
    ACE_Time_Value sleep_250ms( 0, 250000 );

    for ( int update_cnt = 0; update_cnt < 4 * 30; update_cnt++ )
    {
      for ( int deposit = 0; deposit < 6; deposit++ )
      {
        std::string deposit_name( "Deposit/" );
        deposit_name += deposit_tenors[ deposit ];

        deposit_rate_helper2.ObjectId = CORBA::string_dup( deposit_name.c_str() );
        deposit_rate_helper2.Rate = deposit_rates[ deposit ] + sin( static_cast<float>( update_cnt ) )/1000.0;;
        deposit_rate_helper2.Tenor = CORBA::string_dup( deposit_tenors[ deposit ] );

        int ret = deposit_rate_helper2_dw->write( deposit_rate_helper2, deposit_rate_helper2_instance );
        if (ret != DDS::RETCODE_OK) {
          ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Deposit write returned %d.\n"), ret));
        }
      }

      for ( int fra = 0; fra < 3; fra ++ )
      {
        std::stringstream fra_name;

        fra_name << "FRA/"; 
        fra_name << fra_periods_to_start[ fra ];
        fra_name << fra_lenghts_in_months[ fra ];

        fra_rate_helper2.ObjectId = CORBA::string_dup( fra_name.str().c_str() );
        fra_rate_helper2.Rate = fra_rates[ fra ] + sin( static_cast<float>( update_cnt ) )/1000.0;
        fra_rate_helper2.PeriodToStart = CORBA::string_dup( fra_periods_to_start[ fra ] );
        fra_rate_helper2.LengthInMonths = fra_lenghts_in_months[ fra ];

        int ret = fra_rate_helper2_dw->write( fra_rate_helper2, fra_rate_helper2_instance );
        if (ret != DDS::RETCODE_OK) {
          ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Fra write returned %d.\n"), ret));
        }
      }
  
      for ( int swap = 0; swap < 6; swap++ )
      {
        std::string swap_name( "Swap/" );
        swap_name += swap_tenors[ swap ];

        swap_rate_helper2.ObjectId = CORBA::string_dup( swap_name.c_str() );
        swap_rates[ swap ] = swap_rates[ swap ] + sin( static_cast<float>( update_cnt ) )/1000.0;
        swap_rate_helper2.Rate = swap_rates[ swap ];
        swap_rate_helper2.Tenor = CORBA::string_dup( swap_tenors[ swap ] );

        int ret = swap_rate_helper2_dw->write( swap_rate_helper2, swap_rate_helper2_instance );
        if (ret != DDS::RETCODE_OK) {
          ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Swap write returned %d.\n"), ret));
        }
      }
      
      ACE_OS::sleep( sleep_250ms );
    };



  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown ();

  return 0;
}
