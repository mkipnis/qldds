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
#include <pricingenginesTypeSupportImpl.h>
#include <optionsTypeSupportImpl.h>

#include <qldds_convert_utils.h>
#include <BasicDomainParticipant.h>

#include <sstream>

#include <ace/Get_Opt.h>

#include "EquityOptionsTypeSupportImpl.h"
#include "EquityOptionsTypeSupportC.h"

#include "StraddlesTypeSupportImpl.h"
#include "StraddlesTypeSupportC.h"

#include "Common.h"

#include <Addins/Cpp/addincpp.hpp>

#include <qlo/conversions/all.hpp>

#include <qlo/vanillaoption.hpp>
#include <ql/instruments/vanillaoption.hpp>

using namespace QuantLibAddinCpp;


void price( std::string& ticker, qlBlackConstantVolMatrix& vols, qlStrikedTypePayoffSeq& payoffs,
            processes::qlGeneralizedBlackScholesProcess& process, qlEuropeanExerciseSeq& exercises,
            Straddles& straddles, int& priced_options );


int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try 
  {
     QuantLibAddinCpp::initializeAddin();

     boost::gregorian::date date ( boost::gregorian::from_undelimited_string( "20111019" ) );

     long evaluationDate = QuantLib::Date( date.day(), QuantLib::Month(date.month().as_number()), date.year() ).serialNumber(); 

     QuantLibAddinCpp::qlSettingsSetEvaluationDate(evaluationDate, OH_NULL);

     std::string ticker;

     // Initialize, and create a DomainParticipant
     dpf = TheParticipantFactoryWithArgs(argc, argv);
     
     qldds_utils::BasicDomainParticipant participant( dpf, EQUITY_OPTIONS_DOMAIN_ID );
     participant.createPublisher();
     participant.createSubscriber();
     DDS::DomainParticipant_var dp = participant.getDomainParticipant();  

 
     ACE_Get_Opt cmd_opts( argc, argv, ":s:" );
  
     int option;
  
     while ( (option = cmd_opts()) != EOF )
     {
       switch( option )
       {
         case 's' :
           ticker = cmd_opts.opt_arg();
           break;
       }
     }


     // Topics
     // setting up qlBlackConstantVols Topic
     DDS::Topic_var ql_black_constant_vols_topic = participant.createTopicAndRegisterType
        < qlBlackConstantVolsTypeSupport_var, qlBlackConstantVolsTypeSupportImpl >
         ( QL_BLACK_CONSTANT_VOLS_TOPIC_NAME );

     // setting up qlGeneralizedBlackScholesProcesses Topic
     DDS::Topic_var ql_generalized_black_scholes_processes_topic = participant.createTopicAndRegisterType
        < qlGeneralizedBlackScholesProcessesTypeSupport_var, qlGeneralizedBlackScholesProcessesTypeSupportImpl >
         ( QL_GENERALIZED_BLACK_SCHOLES_PROCESSES_TOPIC_NAME );

     // setting up qlStrikedTypePayoff Topic
     DDS::Topic_var ql_striked_type_payoffs_topic = participant.createTopicAndRegisterType
       < qlStrikedTypePayoffsTypeSupport_var, qlStrikedTypePayoffsTypeSupportImpl >
         ( QL_STRIKED_TYPE_PAYOFFS_TOPIC_NAME );

     // setting up qlEuropeanExercises Topic
     DDS::Topic_var ql_european_exercises_topic = participant.createTopicAndRegisterType
        < qlEuropeanExercisesTypeSupport_var, qlEuropeanExercisesTypeSupportImpl >
         ( QL_EUROPEAN_EXERCISES_TOPIC_NAME ); 

     StraddleSetupTypeSupport_var ts_res = new StraddleSetupTypeSupportImpl;
     if ( ts_res->register_type(dp, "") != DDS::RETCODE_OK )
     {
       std::cout << "Registration of the Topic FAILED!!!!" << std::endl;
     }

     CORBA::String_var type_name = ts_res->get_type_name();
     std::cout << "Type Name : " << type_name << std::endl; 

     std::stringstream multi_topic_select;

     multi_topic_select << "SELECT ticker, putVols, callVols, putPayoffs, callPayoffs, process, exercises FROM "<<
                          QL_BLACK_CONSTANT_VOLS_TOPIC_NAME << " NATURAL JOIN " << 
                          QL_GENERALIZED_BLACK_SCHOLES_PROCESSES_TOPIC_NAME << " NATURAL JOIN " <<
                          QL_STRIKED_TYPE_PAYOFFS_TOPIC_NAME << " NATURAL JOIN " << 
                          QL_EUROPEAN_EXERCISES_TOPIC_NAME << " WHERE ticker = '" << ticker << "'";

     std::cout << multi_topic_select.str() << std::endl; 

     DDS::MultiTopic_var mt = dp->create_multitopic("MyMultiTopic", type_name, multi_topic_select.str().c_str(), DDS::StringSeq()); 

     if ( CORBA::is_nil( mt ) ) 
       std::cout << "MultiTopic Subscribtion failed.!!!!" << mt << std::endl;

     DDS::Subscriber_var sub = participant.getSubscriber();
     std::cout << "Creating Data Reader"<< std::endl;
     DDS::DataReader_var dr = sub->create_datareader(mt, DATAREADER_QOS_DEFAULT, 0, ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
     std::cout << "Done..."<< std::endl;

     DDS::WaitSet_var ws = new DDS::WaitSet;
     DDS::ReadCondition_var rc = dr->create_readcondition( DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
     ws->attach_condition(rc);
     DDS::Duration_t infinite = { DDS::DURATION_INFINITE_SEC, DDS::DURATION_INFINITE_NSEC};
     DDS::ConditionSeq active;
     int ret = ws->wait(active, infinite);
     if (ret != DDS::RETCODE_OK) return false;
     ws->detach_condition(rc);

     // setting up topic for Straddles 
     DDS::Topic_var straddles_topic = participant.createTopicAndRegisterType
        < StraddlesTypeSupport_var, StraddlesTypeSupportImpl >
         ( STRADDLES_TOPIC_NAME );

     StraddlesDataWriter_var straddles_dw = participant.createDataWriter
       < StraddlesDataWriter_var, StraddlesDataWriter >
         ( straddles_topic );

     
      int calculation_performed = 0;

      do {
       StraddleSetupDataReader_var res_dr = StraddleSetupDataReader::_narrow(dr);
       StraddleSetupSeq data;
       DDS::SampleInfoSeq info;

       int ret = res_dr->take_w_condition(data, info, DDS::LENGTH_UNLIMITED, rc);

       if (ret == DDS::RETCODE_OK) 
       {
         qlBlackConstantVolMatrix& putVols = data[0].putVols;
         qlStrikedTypePayoffSeq& putPayoffs = data[0].putPayoffs;

         qlBlackConstantVolMatrix& callVols = data[0].callVols;
         qlStrikedTypePayoffSeq& callPayoffs = data[0].callPayoffs;

         processes::qlGeneralizedBlackScholesProcess& process = data[0].process;
         qlEuropeanExerciseSeq& exercises = data[0].exercises;

         Straddles straddles;
         straddles.ticker = CORBA::string_dup( ticker.c_str() );
         straddles.underlying = data[0].process.Underlying; 

         int strike_count = putPayoffs.length() + callPayoffs.length();
         int exercises_count = exercises.length();

         straddles.options.length( strike_count * exercises_count );

         int priced_options = 0;

         price( ticker, putVols, putPayoffs, process, exercises, straddles, priced_options );
         price( ticker, callVols, callPayoffs, process, exercises, straddles, priced_options );

         ACE_DEBUG( (LM_INFO, "(%T|%P|%t) Publishing Straddles for ticker : %s trading @%f\n", ticker.c_str(), data[0].process.Underlying )  );

         int ret = straddles_dw->write( straddles, DDS::HANDLE_NIL );
         if (ret != DDS::RETCODE_OK) {
             ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publishing Straddles for ticker : %s failed %d.\n"), ticker.c_str(), ret));
         }

         calculation_performed++;
       } 
     } while ( calculation_performed < 30 );

    cout << "Exiting..." << endl; 
  } catch (CORBA::Exception& e) 
  {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown(); 
    
  return 0;
}

void price( std::string& ticker, qlBlackConstantVolMatrix& vols, qlStrikedTypePayoffSeq& payoffs,
            processes::qlGeneralizedBlackScholesProcess& process, qlEuropeanExerciseSeq& exercises, 
            Straddles& straddles, int& priced_options )
{
  int strike_count = payoffs.length();

  for ( int strike = 0; strike < strike_count; strike++  )
  {
    std::string payoffType = "Vanilla";

    payoffs::qlStrikedTypePayoff payoff = payoffs[strike];

    std::string idStrikedTypePayoff = QuantLibAddinCpp::qlStrikedTypePayoff(
         payoff.ObjectId.in(),
         payoffType,
         payoff.OptionType.in(),
         static_cast<double>( payoff.Strike ),
         static_cast<double>( payoff.ThirdParameter ),
         OH_NULL,
         OH_NULL,
         true );

    int exercises_count = exercises.length();

    // 0 - Front Month
    for ( int month = 0; month < exercises_count; month++ )
    {
      exercise::qlEuropeanExercise exercise = exercises[ month ];

      std::string idExercise = QuantLibAddinCpp::qlEuropeanExercise(
           exercise.ObjectId.in(),
           qldds_utils::from_iso_string( exercise.ExpiryDate.in() ),
           OH_NULL,
           OH_NULL,
           true );

      std::string engineType = "AE";

      unsigned int skew_index = abs( process.Underlying - payoff.Strike );

      if ( skew_index >= vols[month].length() )
           skew_index = vols[month].length() - 1;

      volatilities::qlBlackConstantVol volatility = vols[month][skew_index];

      std::string volatility_object_id = QuantLibAddinCpp::qlBlackConstantVol (
           volatility.ObjectId.in(),
           qldds_utils::from_iso_string( volatility.SettlementDate.in() ),
           volatility.Calendar.in(),
           static_cast<double>(volatility.Volatility),
           volatility.DayCounter.in(),
           OH_NULL,
           OH_NULL,
           true );

      std::string idGeneralizedBlackScholesProcess = QuantLibAddinCpp::qlGeneralizedBlackScholesProcess (
           process.ObjectId.in(),
           volatility_object_id,
           static_cast<double>( process.Underlying ),
           process.DayCounter.in(),
           qldds_utils::from_iso_string( process.SettlementDate.in() ),
           static_cast<double>( process.RiskFreeRate ),
           static_cast<double>( process.DividendYield ),
           OH_NULL,
           OH_NULL,
           true );

      std::string idPricingEngine = QuantLibAddinCpp::qlPricingEngine(
           "my_engine",
           engineType,
           idGeneralizedBlackScholesProcess,
           OH_NULL,
           OH_NULL,
           true );

      std::string idVanillaOption = QuantLibAddinCpp::qlVanillaOption(
           "my_option",
           idStrikedTypePayoff,
           idExercise,
           OH_NULL,
           OH_NULL,
           true);

      QuantLibAddinCpp::qlInstrumentSetPricingEngine(idVanillaOption, idPricingEngine, OH_NULL);

      Option option;

      std::stringstream name;

      OH_GET_REFERENCE(ObjectIdLibObjPtr, idVanillaOption, QuantLibAddin::VanillaOption, QuantLib::VanillaOption);

      option.option_type = CORBA::string_dup( payoff.OptionType );
      option.strike = payoff.Strike;
      option.expiry_date = CORBA::string_dup( exercise.ExpiryDate );
      option.volatility = volatility.Volatility;

      QuantLib::ClosestRounding closest(3);

      option.npv  =  closest( ObjectIdLibObjPtr->NPV() );
      option.delta  =  closest( ObjectIdLibObjPtr->delta() );
      option.vega   =  closest( ObjectIdLibObjPtr->vega() );
      option.gamma  =  closest( ObjectIdLibObjPtr->gamma() );
      option.theta  =  closest( ObjectIdLibObjPtr->theta() );
      option.rho    =  closest( ObjectIdLibObjPtr->rho() );
      option.expiry_date = CORBA::string_dup( exercise.ExpiryDate );

      straddles.options[ priced_options++ ] = option;
    }
 }

}
