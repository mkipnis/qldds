# Basic Domain Participant #

[BasicDomainParticipant](http://code.google.com/p/qldds/source/browse/qldds_utils/BasicDomainParticipant.h) is a class that provides convenience functions to create publishers, subscribers, thread safe default data readers and data writers.  This class is essentially a wrapper around DDS API.


Example of a publisher for [ratehelpers::SwapRateHelper2:](https://code.google.com/p/qldds/source/browse/Addins/OpenDDS/ratehelpers.idl)

```

DDS::DomainParticipantFactory_var dpf = 
         DDS::DomainParticipantFactory::_nil();
DDS::DomainParticipant_var participant = 
         DDS::DomainParticipant::_nil();

dpf = TheParticipantFactoryWithArgs(argc, argv);

qldds_utils::BasicDomainParticipant participant( dpf, IRS_DOMAIN_ID );
participant.createPublisher();

DDS::Topic_var swap_rate_helper2_topic = 
                       participant.createTopicAndRegisterType
                       < ratehelpers::qlSwapRateHelper2TypeSupport_var,    
                        ratehelpers::qlSwapRateHelper2TypeSupportImpl >
     	            (  SWAP_RATE_HELPER2_TOPIC_NAME );

ratehelpers::qlSwapRateHelper2DataWriter_var swap_rate_helper2_dw = 
                   participant.createDataWriter
   	        < ratehelpers::qlSwapRateHelper2DataWriter_var, 
                   ratehelpers::qlSwapRateHelper2DataWriter >
     	        ( swap_rate_helper2_topic );

ratehelpers::qlSwapRateHelper2 swap_rate_helper2;
DDS::InstanceHandle_t swap_rate_helper2_instance = swap_rate_helper2_dw->register_instance( swap_rate_helper2 );

swap_rate_helper2.ObjectId = CORBA::string_dup(“IRS_10Y”);
swap_rate_helper2.Rate = 0.03165;
swap_rate_helper2.Tenor = CORBA::string_dup(“10Y”);
swap_rate_helper2.Calendar = CORBA::string_dup("TARGET");
swap_rate_helper2.FixedLegFrequency = CORBA::string_dup("Annual");
swap_rate_helper2.FixedLegConvention=CORBA::string_dup("Unadjusted");
swap_rate_helper2.FixedLegDayCounter = CORBA::string_dup("30/360");
swap_rate_helper2.IborIndex =  CORBA::string_dup("Libor");
swap_rate_helper2.ForwardStart =  CORBA::string_dup("0D");
swap_rate_helper2.Spread = 0.0;
swap_rate_helper2.Overwrite = true;

int ret = swap_rate_helper2_dw->write( swap_rate_helper2, swap_rate_helper2_instance );

if (ret != DDS::RETCODE_OK) {
          ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Swap write returned %d.\n"), ret));
}

```



Example of subscriber for [ratehelpers::SwapRateHelper2](https://code.google.com/p/qldds/source/browse/Addins/OpenDDS/ratehelpers.idl) with a [default data reader](DataReaders.md):

```
DDS::DomainParticipantFactory_var dpf = 
DDS::DomainParticipantFactory::_nil();
DDS::DomainParticipant_var participant = 
DDS::DomainParticipant::_nil();

QuantLibAddinCpp::initializeAddin();
QuantLib::Calendar calendar = QuantLib::TARGET();
QuantLib::Date settlementDate(22, QuantLib::September, 2004);
settlementDate = calendar.adjust(settlementDate);

dpf = TheParticipantFactoryWithArgs(argc, argv);

qldds_utils::BasicDomainParticipant irs_participant( dpf, IRS_DOMAIN_ID );
irs_participant.createSubscriber();

QuantLibAddinCpp::qlLibor("Libor", "USD", "6M", "", false, false, true);

DDS::Topic_var swap_rate_helper2_topic = 
                              irs_participant.createTopicAndRegisterType
                              < ratehelpers::qlSwapRateHelper2TypeSupport_var, 
                             ratehelpers::qlSwapRateHelper2TypeSupportImpl >
                             (  SWAP_RATE_HELPER2_TOPIC_NAME );

// This lock synchronizes QuantLib calls
ACE_Mutex qldds_lock;

irs_participant.createDataReaderListener<ratehelpers::qlSwapRateHelper2DataReaderListenerImpl> 
         ( qldds_lock, swap_rate_helper2_topic );
```

---
