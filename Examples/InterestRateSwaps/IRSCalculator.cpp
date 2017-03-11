
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

#include <ql/quantlib.hpp>
#include <Addins/Cpp/addincpp.hpp>
#include <oh/ohdefines.hpp>

#include <scheduleTypeSupportImpl.h>
#include <vanillaswapTypeSupportImpl.h>
#include <ratehelpersTypeSupportImpl.h>

#include <scheduleDataReaderListenerImpl.hpp>
#include <vanillaswapDataReaderListenerImpl.hpp>
#include <ratehelpersDataReaderListenerImpl.hpp>

#include <ace/Get_Opt.h>

#include "Common.h"

#include "IRSPortfolioC.h"
#include "IRSPortfolioTypeSupportC.h"
#include "IRSPortfolioTypeSupportImpl.h"

ACE_Mutex qldds_lock;

ACE_Mutex irs_portfolio_mutex;
std::list< std::string > irs_portfolio;

std::map< std::string, std::vector< std::string> > curves;

ObjectHandler::property_t OH_NULL;

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

bool computeNPVs( std::string& term_structure, IRS::Portfolio& irs_porfolio_out );

class VanillaSwapDataReaderListenerImpl : 
   public vanillaswap::qlVanillaSwapDataReaderListenerImpl
{
  public:

    VanillaSwapDataReaderListenerImpl( ACE_Mutex& mutex ) :
      vanillaswap::qlVanillaSwapDataReaderListenerImpl( mutex ) {};

    virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwap& vanillaswap, std::string& result )
    {
      ACE_Guard<ACE_Mutex> guard( irs_portfolio_mutex );

      irs_portfolio.push_back( result );

      return true;
    }

    virtual void on_std_exception( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwap& vanillaswap, std::exception& e )
    {
      std::cout << "VanillaSwap Exception : " << vanillaswap.ObjectId << ":" << e.what() << std::endl;
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

     // Initialize, and create a DomainParticipant
     dpf = TheParticipantFactoryWithArgs(argc, argv);


     qldds_utils::BasicDomainParticipant irs_participant( dpf, IRS_DOMAIN_ID );
     irs_participant.createPublisher();
     irs_participant.createSubscriber();

     std::string term_structure;

     std::vector<std::string> rate_helpers;

     ACE_Get_Opt cmd_opts( argc, argv, ":c:n:i:" );

     int option;

     while ( (option = cmd_opts()) != EOF )
     {
       switch( option )
       {
         case 'c' :
         { 
           std::istringstream f( cmd_opts.opt_arg() );
           std::string s;

           while (std::getline(f, s, '|')) {
             rate_helpers.push_back(s);
           }
           break;
         }
         case 'n' :
         {
           term_structure = cmd_opts.opt_arg();
           break;
         }
       }
     }

     QuantLibAddinCpp::qlLibor("Libor", "USD", "6M", "", false, false, true);
     
     // Topics for Swap Components
     // Setting up schedule topic
     DDS::Topic_var schedule_topic =
         irs_participant.createTopicAndRegisterType
         < schedule::qlScheduleTypeSupport_var, schedule::qlScheduleTypeSupportImpl >
         ( SCHEDULE_TOPIC_NAME );

     // setting up vanilla swap topic 
     DDS::Topic_var vanilla_swap_topic =
         irs_participant.createTopicAndRegisterType
         < vanillaswap::qlVanillaSwapTypeSupport_var, vanillaswap::qlVanillaSwapTypeSupportImpl >
         ( VANILLA_SWAP_TOPIC_NAME );

 
     // Topics for curve components
     // setting up deposit rate helper
     DDS::Topic_var deposit_rate_helper2_topic = irs_participant.createTopicAndRegisterType
         < ratehelpers::qlDepositRateHelper2TypeSupport_var, ratehelpers::qlDepositRateHelper2TypeSupportImpl >
          ( DEPOSIT_RATE_HELPER2_TOPIC_NAME );

     // setting up FRA Rate helper
     DDS::Topic_var fra_rate_helper2_topic = irs_participant.createTopicAndRegisterType
         < ratehelpers::qlFraRateHelper2TypeSupport_var, ratehelpers::qlFraRateHelper2TypeSupportImpl >
          ( FRA_RATE_HELPER2_TOPIC_NAME );

     // setting up Swap Rate helper
     DDS::Topic_var swap_rate_helper2_topic = irs_participant.createTopicAndRegisterType
       < ratehelpers::qlSwapRateHelper2TypeSupport_var, ratehelpers::qlSwapRateHelper2TypeSupportImpl >
        (  SWAP_RATE_HELPER2_TOPIC_NAME );


    irs_participant.createDataReaderListener< schedule::qlScheduleDataReaderListenerImpl> ( qldds_lock, schedule_topic );
    irs_participant.createDataReaderListener< VanillaSwapDataReaderListenerImpl > ( qldds_lock, vanilla_swap_topic );

    irs_participant.createDataReaderListener< DepositRateHelper2DataReaderListenerImpl > ( qldds_lock,deposit_rate_helper2_topic );
    irs_participant.createDataReaderListener< FraRateHelper2DataReaderListenerImpl > ( qldds_lock, fra_rate_helper2_topic );
    irs_participant.createDataReaderListener< SwapRateHelper2DataReaderListenerImpl > ( qldds_lock, swap_rate_helper2_topic );

    // setting up IRS Portfolio. Priced portfolios will be published on this topic
    DDS::Topic_var irs_portfolio_topic = irs_participant.createTopicAndRegisterType
       < IRS::PortfolioTypeSupport_var, IRS::PortfolioTypeSupportImpl >
        (  IRS_PORTFOLIO_TOPIC_NAME  );

    IRS::PortfolioDataWriter_var irs_portfolio_dw = irs_participant.createDataWriter
      < IRS::PortfolioDataWriter_var, IRS::PortfolioDataWriter >
       ( irs_portfolio_topic );

    curves.insert( std::pair < std::string, std::vector< std::string > > ( term_structure, rate_helpers ) );

    int calculation_performed = 0;

    while ( calculation_performed < 30 )
    {
      IRS::Portfolio irs_portfolio_out;

      if ( computeNPVs( term_structure,  irs_portfolio_out ) == false )
      {
        ACE_Time_Value sleep_100ms( 0, 100000 );
        ACE_OS::sleep( sleep_100ms );

        continue;
      } else {
        calculation_performed++;
        ACE_OS::sleep(1);
      } 

      std::cout << "Calculator ["<< term_structure << "] publishing NPVs for "<< irs_portfolio_out.swaps.length() << " interest rate swaps."<< std::endl; 

      int ret = irs_portfolio_dw->write( irs_portfolio_out, DDS::HANDLE_NIL );
      if (ret != DDS::RETCODE_OK) {
         ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: IRS Portfolio write returned %d.\n"), ret));
      }

    }

  } catch (CORBA::Exception& e)
  {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown();

  return 0;
}

bool computeNPVs( std::string& term_structure, IRS::Portfolio& irs_porfolio_out )
{
  std::vector< std::string >& rate_helpers = curves[ term_structure ]; 

  ACE_Guard<ACE_Mutex> guard( qldds_lock );

  // Check if all curve components have been setup
  std::vector<bool> existing_objects = ObjectHandler::Repository::instance().objectExists( rate_helpers );
  bool all_curve_comp_present = true;

  // Check if all curve pieces have been setup
  for ( unsigned int rate_helper = 0; rate_helper < rate_helpers.size(); rate_helper++ )
  {
     if ( !existing_objects[ rate_helper ] )
     {
       std::cout << "Rate Helper : [" << rate_helpers[ rate_helper ] << "] hasn't been setup yet." << std::endl;
       all_curve_comp_present = false;
     }
  }

  if ( all_curve_comp_present == false )
    return false; 

  std::vector<ObjectHandler::property_t> jumps;

  std::vector<std::string> objects(2);
  objects[0] = term_structure;  // Curve 
  objects[1] = "Libor";  // Index

  std::vector<bool> existing_curve_objects = ObjectHandler::Repository::instance().objectExists( objects );  

  if ( existing_curve_objects[0] == true )
    ObjectHandler::Repository::instance().deleteObject( objects[0] );

  QuantLibAddinCpp::qlPiecewiseYieldCurve( term_structure, static_cast<long>(2), "Target", rate_helpers,
         "Actual/Actual (ISDA)", jumps, jumps, 1.0e-15, "Discount", "LogLinear", false, false, true);

  if ( existing_curve_objects[0] == true )
    ObjectHandler::Repository::instance().deleteObject( objects[1] );
   
  QuantLibAddinCpp::qlLibor("Libor", "USD", "6M", term_structure, false, false, true);

  OH_GET_REFERENCE(IndexLibObjPtr, "Libor", QuantLibAddin::Index, QuantLib::Index);

  IndexLibObjPtr->addFixing(QuantLib::Date(16,QuantLib::September,2004), 0.01, true);

  QuantLibAddinCpp::qlDiscountingSwapEngine( "discountingSwapEngine", term_structure , false, OH_NULL, OH_NULL, false, false, true);

  ACE_Guard<ACE_Mutex> portfolio_guard( irs_portfolio_mutex );

  std::list< std::string >::iterator irs_portfolio_iter;

  int swap_num = 0;

  irs_porfolio_out.term_structure = term_structure.c_str();
  irs_porfolio_out.swaps.length( irs_portfolio.size() );
   
  for ( irs_portfolio_iter = irs_portfolio.begin(); irs_portfolio_iter!=irs_portfolio.end(); irs_portfolio_iter++  )
  {
    IRS::InterestRateSwap swap;

    std::string vanilla_swap = *irs_portfolio_iter;

    swap.swap_description = vanilla_swap.c_str();

    QuantLibAddinCpp::qlInstrumentSetPricingEngine( vanilla_swap, "discountingSwapEngine", false );

    swap.npv = QuantLibAddinCpp::qlInstrumentNPV( vanilla_swap, false );

    irs_porfolio_out.swaps[swap_num] = swap;
    
    swap_num ++;
  }
 
  return true;
};
