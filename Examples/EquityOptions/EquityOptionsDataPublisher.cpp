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


#include <volatilitiesTypeSupportImpl.h>
#include <processesTypeSupportImpl.h>
#include <payoffsTypeSupportImpl.h>
#include <exerciseTypeSupportImpl.h>

#include <sstream>

#include <BasicDomainParticipant.h>

#include "Common.h"

#include "EquityOptionsTypeSupportC.h"
#include "EquityOptionsTypeSupportImpl.h"

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try 
  {
     // Initialize, and create a DomainParticipant
     dpf = TheParticipantFactoryWithArgs(argc, argv);
     
     qldds_utils::BasicDomainParticipant publisher( dpf, EQUITY_OPTIONS_DOMAIN_ID );
     publisher.createPublisher();
     publisher.createSubscriber();

     //
     // Topics
     //
     // setting up qlBlackConstantVols Topic 
     DDS::Topic_var ql_black_constant_vols_topic = publisher.createTopicAndRegisterType
        < qlBlackConstantVolsTypeSupport_var, qlBlackConstantVolsTypeSupportImpl >
         ( QL_BLACK_CONSTANT_VOLS_TOPIC_NAME );

     // setting up qlGeneralizedBlackScholesProcesses Topic 
     DDS::Topic_var ql_generalized_black_scholes_processes_topic = publisher.createTopicAndRegisterType
        < qlGeneralizedBlackScholesProcessesTypeSupport_var, qlGeneralizedBlackScholesProcessesTypeSupportImpl >
         ( QL_GENERALIZED_BLACK_SCHOLES_PROCESSES_TOPIC_NAME );

     // setting up qlStrikedTypePayoff Topic
     DDS::Topic_var ql_striked_type_payoffs_topic = publisher.createTopicAndRegisterType
       < qlStrikedTypePayoffsTypeSupport_var, qlStrikedTypePayoffsTypeSupportImpl >
         ( QL_STRIKED_TYPE_PAYOFFS_TOPIC_NAME );

     // setting up qlEuropeanExercises Topic
     DDS::Topic_var ql_european_exercises_topic = publisher.createTopicAndRegisterType
        < qlEuropeanExercisesTypeSupport_var, qlEuropeanExercisesTypeSupportImpl >
         ( QL_EUROPEAN_EXERCISES_TOPIC_NAME );

    //  Data Writers
    qlBlackConstantVolsDataWriter_var black_constant_vols_dw = publisher.createDataWriter
        < qlBlackConstantVolsDataWriter_var, qlBlackConstantVolsDataWriter >
         ( ql_black_constant_vols_topic );

    qlGeneralizedBlackScholesProcessesDataWriter_var generalized_black_scholes_process_dw = publisher.createDataWriter
        < qlGeneralizedBlackScholesProcessesDataWriter_var, qlGeneralizedBlackScholesProcessesDataWriter >
         ( ql_generalized_black_scholes_processes_topic );

    qlStrikedTypePayoffsDataWriter_var striked_type_payoffs_dw = publisher.createDataWriter
        < qlStrikedTypePayoffsDataWriter_var, qlStrikedTypePayoffsDataWriter >
         ( ql_striked_type_payoffs_topic );

    qlEuropeanExercisesDataWriter_var european_exercises_dw = publisher.createDataWriter
        < qlEuropeanExercisesDataWriter_var, qlEuropeanExercisesDataWriter >
         ( ql_european_exercises_topic );


    std::vector< std::string > tickers(3);
    tickers[0] = "AAA";
    tickers[1] = "BBB";
    tickers[2] = "CCC";

    int number_of_ticker = tickers.size();

    // ATM Volatility
    std::map< std::string, double > atm_vol;
    atm_vol[ tickers[0] ] = 0.10;
    atm_vol[ tickers[1] ] = 0.20;
    atm_vol[ tickers[2] ] = 0.30;

    std::string settlement_date( "20121009" );
    std::string calendar( "TARGET" );
    std::string daycountConvention ( "Actual/365 (Fixed)" );


    qlBlackConstantVols black_constant_vols;
    
    // 
    // Populating Volatility Matrix
    //
    for ( int ticker = 0; ticker < number_of_ticker; ticker++ )
    {
      black_constant_vols.ticker = CORBA::string_dup ( tickers[ ticker ].c_str() );

      black_constant_vols.putVols.length(1); // Front Month Only

      for ( int month = 0; month < 1; month++ ) // Front Month
      {
        black_constant_vols.putVols[month].length( 50 );

        // 0 - at the money strike
        for ( int put_strike = 0; put_strike<50; put_strike++ )
        { 
          volatilities::qlBlackConstantVol putVol;

          putVol.SettlementDate = CORBA::string_dup( settlement_date.c_str() );
          putVol.Calendar = CORBA::string_dup( calendar.c_str() );
          putVol.DayCounter =  CORBA::string_dup( daycountConvention.c_str() );

          std::stringstream object_id;

          object_id << "qlBlackConstantVol/" << tickers[ ticker ] << "/Put/" << put_strike << "/" << settlement_date.c_str();

          putVol.ObjectId = CORBA::string_dup( object_id.str().c_str() );
          putVol.Volatility = atm_vol[ tickers[ ticker ] ] + put_strike / 10.0; 

          black_constant_vols.putVols[month][put_strike] = putVol;
        }

        black_constant_vols.callVols.length(1); // Front Month Only

        black_constant_vols.callVols[month].length( 50 ); 

        // 0 - at the money strike
        for ( int call_strike = 0; call_strike<50; call_strike++ )
        {
          volatilities::qlBlackConstantVol callVol;
         
          callVol.SettlementDate = CORBA::string_dup( settlement_date.c_str() );
          callVol.Calendar = CORBA::string_dup( calendar.c_str() );
          callVol.DayCounter =  CORBA::string_dup( daycountConvention.c_str() );

          std::stringstream object_id;

          object_id << "qlBlackConstantVol/" << tickers[ ticker ] << "/Call/" << call_strike << "/" << settlement_date.c_str();

          callVol.ObjectId = CORBA::string_dup( object_id.str().c_str() );
          callVol.Volatility = atm_vol[ tickers[ ticker ] ] + call_strike / 10.0;

          black_constant_vols.callVols[month][call_strike] = callVol;

        }
      }
     
      cout << "Publishing Black Constant Vol : " << black_constant_vols.ticker << endl;
      int ret = black_constant_vols_dw->write( black_constant_vols, ::DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Black Constant Vol returned %d.\n"), ret));
      }
    }

    
    qlGeneralizedBlackScholesProcesses processes;

    for ( int tt = 0; tt < number_of_ticker; tt++ )
    {
      float underlying = 50; 
      float risk_free_rate = 0.03;

      processes.ticker = CORBA::string_dup ( tickers[ tt ].c_str() );

      processes.process.DayCounter = CORBA::string_dup( daycountConvention.c_str() ); 
      processes.process.SettlementDate = CORBA::string_dup( settlement_date.c_str() );

      std::string object_id;

      processes.process.Underlying = underlying;
      processes.process.RiskFreeRate = risk_free_rate;
	  processes.process.DividendYield = 0.0; 

      object_id = "qlGeneralizedBlackScholesProcess/" + tickers[ tt ] + "/Put";
      processes.process.ObjectId = CORBA::string_dup( object_id.c_str() );

      cout << "Publishing Generalized Black Scholes Process of an Option: " << processes.ticker << endl;
      int ret = generalized_black_scholes_process_dw->write( processes, ::DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Generalized Black Scholes Processes returned %d.\n"), ret));
      }
    } 


    qlStrikedTypePayoffs payoffs;

    for ( int ticker = 0; ticker < number_of_ticker; ticker++ )
    {
      payoffs.ticker = CORBA::string_dup ( tickers[ ticker ].c_str() );

      // 20 to 80 range, with $5 step
      payoffs.putPayoffs.length(12);   
      payoffs.callPayoffs.length(12); 

      int item = 0;

      for ( int strike = 20; strike<80; strike+=5, item++ )
      {
        /* Populating qlStrikedTypePayoff for a Put */
        payoffs::qlStrikedTypePayoff payoffPut;
        
        std::stringstream object_id_put;
        object_id_put << tickers[ ticker ] << "/" << strike << "/" << "Put";
       
        payoffPut.ObjectId = CORBA::string_dup ( object_id_put.str().c_str() );
        payoffPut.OptionType = CORBA::string_dup ( "Put" );
        payoffPut.Strike = strike;
        payoffPut.ThirdParameter = strike;
		
        payoffs.putPayoffs[ item ] = payoffPut;

        /* Populating qlStrikedTypePayoff for a Call */
        payoffs::qlStrikedTypePayoff payoffCall;      

        std::stringstream object_id_call;
        object_id_call << tickers[ ticker ] << "/" << strike << "/" << "Call";

        payoffCall.ObjectId = CORBA::string_dup ( object_id_call.str().c_str() );
        payoffCall.OptionType = CORBA::string_dup ( "Call" );
        payoffCall.Strike = strike;
        payoffCall.ThirdParameter = strike;

        payoffs.callPayoffs[ item ] = payoffCall;
      }

      cout << "Publishing Striked Type Payoff : " << payoffs.ticker << endl;
      int ret = striked_type_payoffs_dw->write( payoffs, ::DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Striked Type Payoff returned %d.\n"), ret));
      }
    }

    qlEuropeanExercises exercises;

    for ( int tt = 0; tt < number_of_ticker; tt++ )
    {
      exercises.ticker = CORBA::string_dup ( tickers[ tt ].c_str() );

      exercises.exercises.length(1);

      std::string object_id;
      object_id = tickers[ tt ] + "/Oct";

      exercise::qlEuropeanExercise exercise;

      exercise.ObjectId = CORBA::string_dup( object_id.c_str() );
      exercise.ExpiryDate = CORBA::string_dup( "20121019" );

      exercises.exercises[0] = exercise;
      
      cout << "Publishing European Exercises : " << exercises.ticker << endl;

      int ret = european_exercises_dw->write( exercises, ::DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing European Exercises returned %d.\n"), ret));
      }
    }

    double underlying = 20;
    double risk_free_rate = 0.03;

    for ( int times = 0; times < 30; times++ ) 
    {
      underlying ++;
 
      for ( int tt = 0; tt < number_of_ticker; tt++ )
      {
        processes.ticker = CORBA::string_dup ( tickers[ tt ].c_str() );

        processes.process.DayCounter = CORBA::string_dup( daycountConvention.c_str() );
        processes.process.SettlementDate = CORBA::string_dup( settlement_date.c_str() );

        std::string object_id;

        processes.process.Underlying = underlying;
        processes.process.RiskFreeRate = risk_free_rate;

        object_id = "qlGeneralizedBlackScholesProcess/" + tickers[ tt ] + "/Put";
        processes.process.ObjectId = CORBA::string_dup( object_id.c_str() );

        cout << "Publishing Generalized Black Scholes Process of an Option: " << processes.ticker << endl;

        int ret = generalized_black_scholes_process_dw->write( processes, ::DDS::HANDLE_NIL );
        if (ret != DDS::RETCODE_OK) {
          ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Generalized Black Scholes Processes returned %d.\n"), ret));
        }
      }

       ACE_OS::sleep(1);
    }

    cout << "Exiting..." << endl;
  } catch (CORBA::Exception& e) 
  {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown();
    
  return 0;
}
