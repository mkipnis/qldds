# Swaptions #

## Scenario: ##
[MarketDataPublisher](https://code.google.com/p/qldds/source/browse/Examples/Swaptions/MarketDataPublisher.cpp) publishes updates on the volatility surface and market data components of a swap curve.  Curve Market Data consists of Deposits, FRAs and SwapRates.  [Two Swaption calculators](https://code.google.com/p/qldds/source/browse/Examples/Swaptions/SwaptionServer.cpp) consume volatility and curve data.  [Client](https://code.google.com/p/qldds/source/browse/Examples/Swaptions/SwaptionClient.cpp) is continuously making synchronous calls to calculators to compute NPV on the provided Swaption indicative data.  That data consists of tenors of an option and an underlying swap, as well as curve and surface names.  This example demonstrates the usage of OpenDDS in conjunction with CORBA.

![https://qldds.googlecode.com/git/misc/Swaptions.jpg](https://qldds.googlecode.com/git/misc/Swaptions.jpg)

## Topics: ##

| **Topic Name** | **TopicType** | **Source** | **Destination** |
|:---------------|:--------------|:-----------|:----------------|
|DEPOSIT\_RATE\_HELPER2\_TOPIC|ratehelpers::qlDepositRateHelper2|MarketDataPublisher|IRSCalculators|
|FRA\_RATE\_HELPER2\_TOPIC|ratehelpers::qlFraRateHelper2|MarketDataPublisher|IRSCalculators|
|SWAP\_RATE\_HELPER2\_TOPIC|ratehelpers::qlSwapRateHelper2|MarketDataPublisher|IRSCalculators|

## Configuring and Compiling: ##
### Unix: ###
```
$ $ACE_ROOT/bin/mwc.pl -type gnuace Swaptions.mwc 
$ make
```

### Windows(Visual Studio Command Prompt 2008): ###
```
> %ACE_ROOT%\bin\mwc.pl -type vc9 Swaptions_vc9.mwc 
> msbuild.exe Swaptions_vc9.sln
```

### Start scripts: ###
```
Unix : run_test.pl
Windows : run_test.bat
```