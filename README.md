# QLDDS - Data Distribution Service for QuantLib

QLDDS is an open source project that simplifies the use of
QuantLib in the distributed environment via
[OpenDDS](https://www.opendds.org). Using QLDDS, the functionality of
the QuantLibAddin/C++ interface may be distributed across
multiple computers running different operating systems, in
real-time. This distribution is accomplished by publishing
and subscribing to DDS data type messages that trigger
corresponding QuantLibAddin calls with the received data.

## Content
QLDDS package includes OMG IDL data types and
corresponding DataReaders autogenerated from QuantLibAddin for
C++. It includes examples and convenience classes that simplify
interaction between OpenDDS, CORBA and QuantLibAddin


## Middleware - Data Distribution Service
QLDDS utilizes [OpenDDS](https://www.opendds.org) as a data
distribution middleware. OpenDDS is an open source
implementation of the OMG Data Distribution Services for
Real-Time System specification. Please review OpenDDS
Developers Guide to get familiar with the basic DDS concepts
before continuing with this document.
[http://download.ociweb.com/OpenDDS/OpenDDS-latest.pdf](http://download.ociweb.com/OpenDDS/OpenDDS-latest.pdf)


## Overview
QLDDS contains converted IDL data types and
corresponding data readers from the QuantLibAddin/C++ function
definitions. Data samples from converted IDL data types are
published to subscribed data readers via DDS topics. Once data
samples are received, they are converted into QuantLibAddin
objects by invoking corresponding QuantLibAddin/C++ calls. IDL
data types and data readers are auto-generated and are located in
```$QLDDS_ROOT/Addins/OpenDDS```


![N|Solid](https://github.com/mkipnis/qldds/blob/qldds-1.22.0/misc/overview.png?raw=true)

## Dependencies

| Project| Version|
| ------ | ------ |
| [OpenDDS](https://www.opendds.org)| 3.22 |
| [QuantLib](https://github.com/lballabio/QuantLib/releases) | 1.22 |
| [ObjectHandler/GenSrc/QuantLibAddinCpp](https://github.com/eehlers/QuantLibAddin-Old/releases/tag/QuantLibAddin-v1.22) | 1.22 |

All QuantLib dependencies need to be configured, compiled
and installed(make install). OpenDDS needs to be configured and
compiled prior to building QLDDS.

## Data Types

OpenDDS data types are defined using IDL ```(see Defining
the Data Types in OpenDDS Developer Guide)```
The auto generated IDL data types are located in
```$QLDDS_ROOT/Addins/OpenDDS```


Example of qlSwapRateHelper2 Data Type from ratehelpers.idl:
```bash
#pragma DCPS_DATA_TYPE "ratehelpers::qlSwapRateHelper2"
#pragma DCPS_DATA_KEY "ratehelpers::qlSwapRateHelper2 instanceID"

struct qlSwapRateHelper2 {
   string instanceID;
   string ObjectId;
   double Rate;
   string Tenor;
   string Calendar;
   string FixedLegFrequency;
   string FixedLegConvention;
   string FixedLegDayCounter;
   string IborIndex;
   double Spread;
   string ForwardStart;
   string DiscountingCurve;
   boolean Permanent;
   boolean Trigger;
  boolean Overwrite;
};
```

OpenDDS provides a compiler that generates the code to
marshal and demarshal idl messages, as well as type support
code for data readers and writers `(see Processing the IDL in
OpenDDS Developers Guide)`

Example of using generated C++ code for qlSwapRateHelper2:

```bash
ratehelpers::qlSwapRateHelper2 swap_rate_helper2;

swap_rate_helper2.ObjectId = CORBA::string_dup(“IRS_10Y”);
swap_rate_helper2.Rate = 0.03165;
swap_rate_helper2.Tenor = CORBA::string_dup(“10Y”);
swap_rate_helper2.Calendar = CORBA::string_dup("TARGET");
swap_rate_helper2.FixedLegFrequency = CORBA::string_dup("Annual");
swap_rate_helper2.FixedLegConvention=CORBA::string_dup("Unadjusted");
swap_rate_helper2.FixedLegDayCounter = CORBA::string_dup("30/360");
swap_rate_helper2.IborIndex = CORBA::string_dup("Libor");
swap_rate_helper2.ForwardStart = CORBA::string_dup("0D");
swap_rate_helper2.Spread = 0.0;
swap_rate_helper2.Overwrite = true;
```

### Default Data Readers

Default Data Readers are derived from
qldds::DataReaderListener. qldds::DataReaderListener is an
abstract class defined in DataReaderListener.hpp, located in
$QLDDS_ROOT/qldds_utils. qldds::DataReaderListener is derived
from DDS::DataReaderListener and has a number of additional
pure virtual functions that will be called during data reading. These
calls include reading start, reading end, pre and post QuantLibAddin
function calls, as well as calls during exceptions

![N|Solid](https://github.com/mkipnis/qldds/blob/qldds-1.12.0/misc/datareaders.png?raw=true)

Default DataReaders are autogenerated from
QuantLibAddin/C++ XML function definitions using
qldds_gensrc.py. Default Data Readers are included in the
package and are located at $QLDDS_ROOT/Addins/OpenDDS.
Below is an incomplete class declaration of a default data
reader for qlSwapRateHelper2 data type. The complete class
declaration can be found in
$QLDDS_ROOT/Addins/OpenDDS/ratehelpersDataReaderListenerI
mpl.hpp

```bash
class qlSwapRateHelper2DataReaderListenerImpl : public virtual OpenDDS::DCPS::LocalObject
<qldds::DataReaderListener< ratehelpers::qlSwapRateHelper2, std::string > >;
```

Note that qldds::DataReaderListener takes two template
parameters. First parameter indicates QLDDS datatype which is
ratehelpers::qlSwapRateHelper2 in case of
qlSwapRateHelper2DataReaderListenerImpl. Second parameter
indicates the type returned by a particular QuantLibAddin call which
is a std::string returned by QuantLibAddinCpp::qlSwapRateHelper2
in this case. A reference to an instance of an object of the first
template parameter is being passed to pre_quantlib_addin_call
and post_quantlib_addin_call. A reference to an instance of an
object of the second template parameter is being passed to
post_quantlib_addin_call.
Below is a snapshot of an autogenerated code of
on_data_available for qlSwapRateHelper2DataReaderListenerImpl.
Complete declaration can be found in
$QLDDS_ROOT/Addins/OpenDDS/
ratehelpersDataReaderListenerImpl.cpp

```bash
ratehelpers::qlSwapRateHelper2 obj;
DDS::SampleInfo si ;
DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

if ( status == DDS::RETCODE_OK && si.valid_data == true )
{
   if ( si.valid_data == true )
   {
      ++count;
      if ( pre_quantlib_addin_call( reader, si, obj ) )
      {
         std::string returnObject;;

         try {
             ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

             returnObject = QuantLibAddinCpp::qlSwapRateHelper2 (
                            obj.ObjectId.in(),
                            obj.Rate ,
                            obj.Tenor.in(),
                            obj.Calendar.in(),
                            obj.FixedLegFrequency.in(),
                            obj.FixedLegConvention.in(),
                            obj.FixedLegDayCounter.in(),
                            obj.IborIndex.in(),
                            obj.Spread ,
                            obj.ForwardStart.in(),
                            obj.DiscountingCurve.in(),
                            static_cast<bool>(obj.Permanent),
                            obj.Trigger,
                            static_cast<bool>(obj.Overwrite) );
           } catch ( std::exception& e )
           {
                on_std_exception( reader, obj, e );
                continue;
           }

           if ( !post_quantlib_addin_call( reader, obj, returnObject ) )
              break;
      }
}
```


## Threading

OpenDDS creates a separate thread to handle transport
I/O events(see Threading in OpenDDS Developers Guide). Since
QuantLib, ObjectHandler and QuantLibAddin for C++ are not thread
safe libraries, all calls to these components must be synchronized
when called from different threads. Constructors of Default Data
Readers accept a reference to an ACE_Mutex object that will be
locked before making a QuantLibAddin for C++ call and released
after the call is complete.

## BasicDomainParticipant

BasicDomainParticipant is a class that provides
convenience functions to create publishers, subscribers, thread
safe default data readers and data writers. This class is essentially
a wrapper around DDS API. BasicDomainParticipant can be found
in $QLDDS_ROOT/qldds_utils/BasicDomainParticipant.hpp
Example of a publisher for ratehelpers::SwapRateHelper2 :

```bash
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
        ( SWAP_RATE_HELPER2_TOPIC_NAME );

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
swap_rate_helper2.IborIndex = CORBA::string_dup("Libor");
swap_rate_helper2.ForwardStart = CORBA::string_dup("0D");
swap_rate_helper2.Spread = 0.0;
swap_rate_helper2.Overwrite = true;

int ret = swap_rate_helper2_dw->write( swap_rate_helper2, swap_rate_helper2_instance );
if (ret != DDS::RETCODE_OK) {
    ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Swap write returned %d.\n"), ret));
}
```

### Example of subscriber for ratehelpers::SwapRateHelper2 with a default DataReader:
``` bash
DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();
QuantLibAddinCpp::initializeAddin();

QuantLib::Calendar calendar = QuantLib::TARGET();
QuantLib::Date settlementDate(22, QuantLib::September, 2004);
settlementDate = calendar.adjust(settlementDate);

dpf = TheParticipantFactoryWithArgs(argc, argv);
qldds_utils::BasicDomainParticipant irs_participant( dpf, IRS_DOMAIN_ID );

irs_participant.createSubscriber();
QuantLibAddinCpp::qlLibor("Libor", "USD", "6M", "", false, false, true);
DDS::Topic_var swap_rate_helper2_topic = irs_participant.createTopicAndRegisterType
        < ratehelpers::qlSwapRateHelper2TypeSupport_var, ratehelpers::qlSwapRateHelper2TypeSupportImpl >
        ( SWAP_RATE_HELPER2_TOPIC_NAME );

// This lock synchronizes QuantLib calls
ACE_Mutex qldds_lock;
irs_participant.createDataReaderListener<ratehelpers::qlSwapRateHelper2DataReaderListenerImpl>
        ( qldds_lock, swap_rate_helper2_topic );
```
## Configuring and Building QLDDS
QLDDS can be configured using configure.py located in
the root directory of the package. This script creates an
environment file with all the necessary variables for this package.
Usage:
Unix (Assuming all dependences were installed under
$HOME):

``` bash
$ python configure.py --dds_dir=$HOME/DDS --boost_dir=$HOME --quantlib_dir=$HOME --oh_dir=$HOME --qladdin_dir=$HOME
```

Upon the successful execution of the configuration script the following file with environment variables will be created in the root directory of the package:  Unix - qldds_env.sh
This file should be sourced before building other components of the package.

## AutoGeneration of DataTypes and DataReaders

$QLDDS_HOME/gensrc/qldds_gensrc.py is a script that converts QuantLibAddin for C++ XML function definitions to IDL
and creates default implementation of DataReaders for converted types. This script requires locations of source directories of ObjectHander, GenSrc and QuantLibAddin that can be passed as command arguments

``` bash 
$ python qldds_gensrc.py --oh_dir=$HOME/ObjectHandler-1.12.0 --gensrc_dir=$HOME/gensrc-1.12.0
     --qladdin_dir=$HOME/QuantLibAddin-1.12.0
```
#
## Examples:

### Interest Rate Swaps
#### Scenario:

InstrumentDataPublisher publishes interest rate swap
contract information. MarketDataPublisher publishes components
of swap curves that include Deposits, FRAs and Swaps. Two
calculators subscribe to swap contract information and market
data, reprice received swaps against the latest market data and
republish priced portfolio of swaps to clients. (Fig 3.0)
(Fig 3.0)

InstrumentPublishesher continuously publishes contract information to IRScalculators. Swap contract information
consists of schedule::qlSchedule and vanillaswap::qlVanillaSwap
QLDDS data types. Upon publishing each of the samples of a
given data type, publisher waits for an acknowledgement from
each of the subscribers/IRSCalculators.

Market Data Publisher continuously publishes updates on
the instrument components of a swap curve that include samples
of ratehelpers::qlDepositRateHelper2,
ratehelpers::qlFraRateHelper2 and
ratehelpers::qlSwapRateHelper2 QLDDS data types.

IRSCalculators subscribe to all listed above data types, once per second, reprice all swaps against the latest market data with specified in command line curve. Priced interest rate swaps are subsequently published in form of a portfolio to three clients.

![N|Solid](https://github.com/mkipnis/qldds/blob/qldds-1.12.0/misc/irs_example.png?raw=true)

#### Curves :
| Calculator A | Calculator B|
|--------------|-------------|
|Deposit/1M|Deposit/1M|
|Deposit/3M|Deposit/3M|
|FRA/6M9|Deposit/6M|
|FRA/6M12|Deposit/1Y|
|Swap/2Y|Swap/2Y|
|Swap/5Y|Swap/5Y|
|Swap/10Y|Swap/10Y|
|Swap/15Y|Swap/15Y|
|Swap/50Y|Swap/50Y|

Clients subscribe to priced swap portfolio data and display
portfolio NPVs on the screen.

#### Topics:

|Topic Name |Topic Type|Source |Destination|
|-----------|----------|-------|-----------|
|SCHEDULE_TOPIC|schedule::qlSchedule|InstrumentDataPublisher|IRSCalculator|
|VANILLA_SWAP_TOPIC|vanillaswap::qlVanillaSwap|InstrumentDataPublisher|IRSCalculator
|DEPOSIT_RATE_HELPER2_TOPIC|ratehelpers::qlDepositRateHelper2|MarketDataPublisher|IRSCalculator
|FRA_RATE_HELPER2_TOPIC|ratehelpers::qlFraRateHelper2|MarketDataPublisher|IRSCalculator
|SWAP_RATE_HELPER2_TOPIC|ratehelpers::qlSwapRateHelper2|MarketDataPublisher|IRSCalculator
|IRS_PORTFOLIO_TOPIC|IRS::Portfolio|IRSCalculator|Client

#### Configuring and Compiling:
``` bash
$ $ACE_ROOT/bin/mwc.pl -type gnuace InterestRateSwaps.mwc
$ make
```

#### start script:
``` bash
$ ./run_test.pl
```
#
### Swaptions
#### Scenario:


MarketDataPublisher continuously publishes updates on swaption vol
surface and market data components of the underlying swap curve. Curve
components consist of Deposits, FRAs and SwapRates. Two
Swaption calculators consume volatility and curve data. Client
continuously publishing requests to compute
NPV on swaptions with various expirations and underlying swap maturities. Calculators consume pricing requests, compute NPVs, break even rates, and publish results back to the client.
Client displays results along with the name of the calculator that replied first.

![N|Solid](https://github.com/mkipnis/qldds/blob/qldds-1.12.0/misc/swaption_example.png?raw=true)


#### Configuring and Compiling:
``` bash
$ $ACE_ROOT/bin/mwc.pl -type gnuace Swaptions.mwc
$ make
```
#
### Equity Options
#### Scenario:

DataPublisher publishes indicative and market data
information for 20 put and call strikes for three stock tickers.
Three calculators(EquityOptionServers) subscribe to indicative and
market data for a given stock ticker. They compute NPVs and
Greeks on puts and calls of received strikes and publish results to
clients. Two clients receive data published by 3 calculators and
display the results. (See Fig 5.0) This example also demonstrates
the multi-topic subscription feature of OpenDDS by having
sequences of BlackContantVols,
GeneralizedBlackScholesProcesses, StickedTypePayoffs and
EuropeanExcercises published by the DataPublisher and joined on
the ticker by the EquityOptionServer.

![N|Solid](https://github.com/mkipnis/qldds/blob/qldds-1.12.0/misc/options_examples.jpg?raw=true)

#### Configuring and Compiling:
``` bash
$ $ACE_ROOT/bin/mwc.pl -type gnuace EquityOptions.mwc
$ make
````
#
### Curve Builder - Java Client
#### Scenario:
Java client publishes curve components, market data and to be priced curve tenors to CurvePricer.  CurvePricer constructs yield curve from received components, calculates rates for provided tenors and publishes back results.  Java Client displays calculated rates on the screen.

![N|Solid](https://github.com/mkipnis/qldds/blob/qldds-1.12.0/misc/java_curve_builder_example.png?raw=true)

#### Configuring and Compiling
``` bash
$ cd $QLDDS_ROOT/java
$ $ACE_ROOT/bin/mwc.pl -type gnuace
$ make
````
#### Start Script:
``` bash
$ cd Examples/CurveBuilder
$ ./run_test.sh
```
