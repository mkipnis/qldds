#include <BasicDomainParticipant.h>
#include <ratehelpersTypeSupportImpl.h>
#include <swaptionvolstructureTypeSupportImpl.h>

#include "Common.h"

#include <math.h>

using namespace qldds_utils;

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try {

    dpf = TheParticipantFactoryWithArgs(argc, argv);

    qldds_utils::BasicDomainParticipant participant( dpf, SWAPTION_DOMAIN_ID );
    participant.createPublisher();

    // Topics
    // setting up deposit rate helper
    DDS::Topic_var topic_deposit_rate_helper2 = participant.createTopicAndRegisterType
        < ratehelpers::qlDepositRateHelper2TypeSupport_var, ratehelpers::qlDepositRateHelper2TypeSupportImpl >
         ( DEPOSIT_RATE_HELPER2_TOPIC_NAME );

    // setting up FRA Rate helper
    DDS::Topic_var topic_fra_rate_helper2 = participant.createTopicAndRegisterType
        < ratehelpers::qlFraRateHelper2TypeSupport_var, ratehelpers::qlFraRateHelper2TypeSupportImpl >
         ( FRA_RATE_HELPER2_TOPIC_NAME );

    // setting up Swap Rate helper
    DDS::Topic_var topic_swap_rate_helper2 = participant.createTopicAndRegisterType
      < ratehelpers::qlSwapRateHelper2TypeSupport_var, ratehelpers::qlSwapRateHelper2TypeSupportImpl >
       (  SWAP_RATE_HELPER2_TOPIC_NAME );

    // setting up Swaption VTS Martrix
    DDS::Topic_var topic_swaption_vts_matrix = participant.createTopicAndRegisterType
      < swaptionvolstructure::qlSwaptionVTSMatrixTypeSupport_var, swaptionvolstructure::qlSwaptionVTSMatrixTypeSupportImpl >
       (  SWAPTION_VTS_MATRIX_TOPIC_NAME );

    //  Data Writers
   ratehelpers::qlDepositRateHelper2DataWriter_var dw_deposit_rate_helper2 = participant.createDataWriter
      < ratehelpers::qlDepositRateHelper2DataWriter_var, ratehelpers::qlDepositRateHelper2DataWriter >
       ( topic_deposit_rate_helper2 );

    ratehelpers::qlFraRateHelper2DataWriter_var dw_fra_rate_helper2 = participant.createDataWriter
      < ratehelpers::qlFraRateHelper2DataWriter_var, ratehelpers::qlFraRateHelper2DataWriter >
       ( topic_fra_rate_helper2 );

    ratehelpers::qlSwapRateHelper2DataWriter_var dw_swap_rate_helper2 = participant.createDataWriter
      < ratehelpers::qlSwapRateHelper2DataWriter_var, ratehelpers::qlSwapRateHelper2DataWriter >
       ( topic_swap_rate_helper2 );

    swaptionvolstructure::qlSwaptionVTSMatrixDataWriter_var dw_swaption_vts_matrix = participant.createDataWriter
      < swaptionvolstructure::qlSwaptionVTSMatrixDataWriter_var, swaptionvolstructure::qlSwaptionVTSMatrixDataWriter >
       ( topic_swaption_vts_matrix );


    ratehelpers::qlDepositRateHelper2 deposit_rate_helper2;
    DDS::InstanceHandle_t instance_deposit_rate_helper2 = 
      dw_deposit_rate_helper2->register_instance( deposit_rate_helper2 );

    ratehelpers::qlFraRateHelper2 fra_rate_helper2;
    DDS::InstanceHandle_t instance_fra_rate_helper2 = dw_fra_rate_helper2->register_instance( fra_rate_helper2 );

    ratehelpers::qlSwapRateHelper2 swap_rate_helper2;
    DDS::InstanceHandle_t instance_swap_rate_helper2 = dw_swap_rate_helper2->register_instance( swap_rate_helper2 );

    swaptionvolstructure::qlSwaptionVTSMatrix swaption_vts_matrix;
    DDS::InstanceHandle_t instance_swaption_vts_matrix = dw_swaption_vts_matrix->register_instance( swaption_vts_matrix );

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
    fra_rate_helper2.PillarDate = CORBA::string_dup("LastRelevantDate");
    fra_rate_helper2.Overwrite = true;

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

    swap_rate_helper2.Calendar = CORBA::string_dup("TARGET");
    swap_rate_helper2.FixedLegFrequency = CORBA::string_dup("Annual");
    swap_rate_helper2.FixedLegConvention = CORBA::string_dup("Unadjusted");
    swap_rate_helper2.FixedLegDayCounter = CORBA::string_dup("30/360");
    swap_rate_helper2.IborIndex =  CORBA::string_dup("Libor");
    swap_rate_helper2.ForwardStart =  CORBA::string_dup("0D");
    swap_rate_helper2.Spread = 0.0;
    swap_rate_helper2.PillarDate = CORBA::string_dup("LastRelevantDate");
    swap_rate_helper2.Overwrite = true;

    // Swaption Vol Matrix
    swaption_vts_matrix.ObjectId = CORBA::string_dup("SwaptionVTSMatrix");  
    swaption_vts_matrix.Calendar = CORBA::string_dup("TARGET");
    swaption_vts_matrix.BusinessDayConvention = CORBA::string_dup("Unadjusted");
    swaption_vts_matrix.DayCounter = CORBA::string_dup("30/360 (Eurobond Basis)");

    StringSeq optionTenors;
    StringSeq swapTenors;
   
    optionTenors.length(5);
    optionTenors[0] = CORBA::string_dup("5D");
    optionTenors[1] = CORBA::string_dup("1M");
    optionTenors[2] = CORBA::string_dup("3M");
    optionTenors[3] = CORBA::string_dup("6M");
    optionTenors[4] = CORBA::string_dup("1Y");
   
    swaption_vts_matrix.OptionTenors = optionTenors;

    swapTenors.length(6);
    swapTenors[0] = CORBA::string_dup("1Y");
    swapTenors[1] = CORBA::string_dup("3Y");
    swapTenors[2] = CORBA::string_dup("5Y");
    swapTenors[3] = CORBA::string_dup("7Y");
    swapTenors[4] = CORBA::string_dup("10Y");
    swapTenors[5] = CORBA::string_dup("15Y");

    swaption_vts_matrix.SwapTenors = swapTenors;

    qldds_utils::Matrix volatilities;
    
    volatilities.length(5);
    volatilities[0].length(6); 
    volatilities[1].length(6); 
    volatilities[2].length(6); 
    volatilities[3].length(6); 
    volatilities[4].length(6); 

    volatilities[0][0] = 0.10;
    volatilities[0][1] = 0.11;
    volatilities[0][2] = 0.12;
    volatilities[0][3] = 0.13;
    volatilities[0][4] = 0.14;
    volatilities[0][5] = 0.15;

    volatilities[1][0] = 0.20;
    volatilities[1][1] = 0.21;
    volatilities[1][2] = 0.22;
    volatilities[1][3] = 0.23;
    volatilities[1][4] = 0.24;
    volatilities[1][5] = 0.25;

    volatilities[2][0] = 0.30;
    volatilities[2][1] = 0.31;
    volatilities[2][2] = 0.32;
    volatilities[2][3] = 0.33;
    volatilities[2][4] = 0.34;
    volatilities[2][5] = 0.35;

    volatilities[3][0] = 0.40;
    volatilities[3][1] = 0.41;
    volatilities[3][2] = 0.42;
    volatilities[3][3] = 0.43;
    volatilities[3][4] = 0.44;
    volatilities[3][5] = 0.45;

    volatilities[4][0] = 0.50;
    volatilities[4][1] = 0.51;
    volatilities[4][2] = 0.52;
    volatilities[4][3] = 0.53;
    volatilities[4][4] = 0.54;
    volatilities[4][5] = 0.55;

    swaption_vts_matrix.Volatilities = volatilities;
    
    
    ACE_Time_Value sleep_250ms( 0, 250000 );

    //
    // Market data will be published for 10 seconds at the rate of 4 updates a second
    //
    for ( int tt = 0; tt < 4 * 10; tt++ )
    {
      for ( int deposit = 0; deposit < 6; deposit++ )
      {
        std::string deposit_name( "Deposit/" );
        deposit_name += deposit_tenors[ deposit ];

        deposit_rate_helper2.ObjectId = CORBA::string_dup( deposit_name.c_str() );
        deposit_rate_helper2.Rate = deposit_rates[ deposit ] + sin( static_cast<float>(tt) )/1000.0;;
        deposit_rate_helper2.Tenor = CORBA::string_dup( deposit_tenors[ deposit ] );

        int ret = dw_deposit_rate_helper2->write( deposit_rate_helper2, instance_deposit_rate_helper2 );
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
        fra_rate_helper2.Rate = fra_rates[ fra ] + sin( static_cast<float>(tt) )/1000.0;
        fra_rate_helper2.PeriodToStart = CORBA::string_dup( fra_periods_to_start[ fra ] );
        fra_rate_helper2.LengthInMonths = fra_lenghts_in_months[ fra ];

        int ret = dw_fra_rate_helper2->write( fra_rate_helper2, instance_fra_rate_helper2 );
        if (ret != DDS::RETCODE_OK) {
          ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Fra write returned %d.\n"), ret));
        }
      }
  
      for ( int swap = 0; swap < 6; swap++ )
      {
        std::string swap_name( "Swap/" );
        swap_name += swap_tenors[ swap ];

        swap_rate_helper2.ObjectId = CORBA::string_dup( swap_name.c_str() );
        swap_rates[ swap ] = swap_rates[ swap ] + sin( static_cast<float>(tt) )/1000.0;
        swap_rate_helper2.Rate = swap_rates[ swap ];
        swap_rate_helper2.Tenor = CORBA::string_dup( swap_tenors[ swap ] );

        int ret = dw_swap_rate_helper2->write( swap_rate_helper2, instance_swap_rate_helper2 );
        if (ret != DDS::RETCODE_OK) {
          ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Swap write returned %d.\n"), ret));
        }
      }

      for ( int opt_tenor = 0; opt_tenor<5; opt_tenor++ )
      {
        for ( int swap_tenor = 0; swap_tenor < 6; swap_tenor++ )
        {
          volatilities[opt_tenor][swap_tenor] += sin( static_cast<float>(tt) )/10.0;
        } 
      }
 
      int ret = dw_swaption_vts_matrix->write( swaption_vts_matrix, instance_swaption_vts_matrix );
      if (ret != DDS::RETCODE_OK) {
         ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Swaption VTS matrix returned %d.\n"), ret));
      }
      
      tt++;
     
      ACE_OS::sleep( sleep_250ms );
    };

  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown ();

  return 0;
}
