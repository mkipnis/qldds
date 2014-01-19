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


#include <scheduleTypeSupportImpl.h>
#include <vanillaswapTypeSupportImpl.h>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <BasicDomainParticipant.h>
#include <math.h>

#include "Common.h"

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try {

    dpf = TheParticipantFactoryWithArgs(argc, argv);

    qldds_utils::BasicDomainParticipant participant( dpf, IRS_DOMAIN_ID );
    participant.createPublisher();

    // Setting up schedule topic
    DDS::Topic_var schedule_topic = participant.createTopicAndRegisterType
      < schedule::qlScheduleTypeSupport_var, schedule::qlScheduleTypeSupportImpl >
       ( SCHEDULE_TOPIC_NAME );

    // Setting up Vanilla Swap Topic
    DDS::Topic_var vanilla_swap_topic = participant.createTopicAndRegisterType
      < vanillaswap::qlVanillaSwapTypeSupport_var, vanillaswap::qlVanillaSwapTypeSupportImpl >
       ( VANILLA_SWAP_TOPIC_NAME );

    // Setting up Schedule DataWriter
    schedule::qlScheduleDataWriter_var schedule_dw = participant.createDataWriter
       < schedule::qlScheduleDataWriter_var, schedule::qlScheduleDataWriter >
         ( schedule_topic );

    // Setting up VanillaSwapDataWriter DataWriter
    vanillaswap::qlVanillaSwapDataWriter_var vanilla_swap_dw = participant.createDataWriter
      < vanillaswap::qlVanillaSwapDataWriter_var, vanillaswap::qlVanillaSwapDataWriter >
        ( vanilla_swap_topic );

    //
    // Objects of qlSchedule and qlVanillaSwap to be reused with every publication
    //
    schedule::qlSchedule fixed_leg_schedule;

    fixed_leg_schedule.Tenor = CORBA::string_dup("1Y");
    fixed_leg_schedule.Calendar = CORBA::string_dup("TARGET");
    fixed_leg_schedule.Convention =  CORBA::string_dup("Unadjusted");
    fixed_leg_schedule.TermDateConv = CORBA::string_dup("Unadjusted");
    fixed_leg_schedule.GenRule = CORBA::string_dup("Forward");
    fixed_leg_schedule.EndOfMonth = false;

    schedule::qlSchedule floating_leg_schedule;

    floating_leg_schedule.Tenor = CORBA::string_dup("6M");
    floating_leg_schedule.Calendar = CORBA::string_dup("TARGET");
    floating_leg_schedule.Convention =  CORBA::string_dup("Modified Following");
    floating_leg_schedule.TermDateConv = CORBA::string_dup("Modified Following");
    floating_leg_schedule.GenRule = CORBA::string_dup("Forward");
    floating_leg_schedule.EndOfMonth = false;

    vanillaswap::qlVanillaSwap vanilla_swap;

    vanilla_swap.FixDayCounter = CORBA::string_dup("30/360 (Eurobond Basis)");
    vanilla_swap.IborIndex =  CORBA::string_dup("Libor");
    vanilla_swap.FloatingLegDayCounter = CORBA::string_dup("ACT/360");
    vanilla_swap.PaymentConvention = CORBA::string_dup("Unadjusted");
    vanilla_swap.Spread = 0.0;

    std::string iso_date("20080915");

    boost::gregorian::date date ( boost::gregorian::from_undelimited_string(iso_date) );
    const std::locale fmt( std::locale::classic(), new boost::gregorian::date_facet("%m/%d/%Y") );

    int duration = 0; // Duration in years

    ACE_Time_Value sleep_1ms( 0, 1000 );

    //
    //  Publishing qlSchedule and qlVanillaSwap
    //
    for ( int swap = 0; swap<100; swap++ )
    {
      boost::gregorian::date start_date = date;
      boost::gregorian::date end_date = start_date+boost::gregorian::years( ++duration );
   
      if ( duration == 30 ) duration = 0;

      std::string start_date_str( boost::gregorian::to_iso_string( start_date ) );
      std::string end_date_str( boost::gregorian::to_iso_string( end_date ) );

      std::string fixed_schedule_description = "FixedLegSchedule-";
      fixed_leg_schedule.EffectiveDate = CORBA::string_dup( start_date_str.c_str() );
      fixed_leg_schedule.TerminationDate = CORBA::string_dup( end_date_str.c_str() );
      fixed_schedule_description += start_date_str + "-" + end_date_str + "-" + boost::lexical_cast<std::string>( swap );  
      fixed_leg_schedule.ObjectId = CORBA::string_dup( fixed_schedule_description.c_str() );

      std::string floating_schedule_description = "FloatingLegSchedule-";
      floating_leg_schedule.EffectiveDate = CORBA::string_dup( start_date_str.c_str() );
      floating_leg_schedule.TerminationDate = CORBA::string_dup( end_date_str.c_str() );
      floating_schedule_description += start_date_str + "-" + end_date_str + "-" + boost::lexical_cast<std::string>( swap );
      floating_leg_schedule.ObjectId = CORBA::string_dup( floating_schedule_description.c_str() );

      std::string pay_or_receive( swap%2==0 ? "RECEIVER": "PAYER" );
      vanilla_swap.FixSchedule = fixed_leg_schedule.ObjectId;
      vanilla_swap.FloatingLegSchedule = floating_leg_schedule.ObjectId;
      vanilla_swap.PayerReceiver = CORBA::string_dup( pay_or_receive.c_str() );

      float fixed_rate = 3.0 + sin( static_cast< float > ( swap ) );
      fixed_rate = floor( fixed_rate * pow(10.0, 2) + 0.5) / pow(10.0, 2); // Rounding
      
      std::stringstream swap_description; 
      swap_description.imbue( fmt ); 
      swap_description << pay_or_receive << " " << fixed_rate << " " << end_date;

      vanilla_swap.ObjectId = CORBA::string_dup( swap_description.str().c_str() );
      vanilla_swap.Nominal = 1000000.0;
      vanilla_swap.FixedRate = fixed_rate / 100.0;

      ACE_DEBUG( (LM_INFO, "(%T|%P|%t) Publishing Fixed Schedule of the Swap: %s\n", fixed_leg_schedule.ObjectId.in() ) );
      int ret = schedule_dw->write( fixed_leg_schedule, DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Fixed Schedule of the Swap returned %d.\n"), ret));
      }

      DDS::Duration_t delay = { 5, 0 };
      DDS::ReturnCode_t result;

      result = schedule_dw->wait_for_acknowledgments( delay );
      if ( result != ::DDS::RETCODE_OK ) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Wait for Schedule publisher fail %d.\n"), result));
      }

      ACE_DEBUG( (LM_INFO, "(%T|%P|%t) Publishing Floating Leg Schedule of the Swap: %s\n", floating_leg_schedule.ObjectId.in() ) );
      ret = schedule_dw->write( floating_leg_schedule, DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Floating Leg Schedule of the Swap returned %d.\n"), ret));
      }

      result = schedule_dw->wait_for_acknowledgments( delay );
      if ( result != ::DDS::RETCODE_OK ) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Wait for Schedule publisher fail %d.\n"), result));
      }

      ACE_DEBUG( (LM_INFO, "(%T|%P|%t) Publishing Vanilla Swap: %s\n", vanilla_swap.ObjectId.in() ) );
      ret = vanilla_swap_dw->write( vanilla_swap, DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Vanilla Swap returned %d.\n"), ret));
      }

      result = vanilla_swap_dw->wait_for_acknowledgments( delay );
      if ( result != ::DDS::RETCODE_OK ) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Wait for Vanilla Swap publisher fail %d.\n"), result));
      }

      ACE_OS::sleep( sleep_1ms ); 
    }

    ACE_OS::sleep( 10 ); 

  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown ();

  return 0;
}
