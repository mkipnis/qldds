# Interest Rate Swaps #

## Scenario: ##

**InstrumentDataPublisher** publishes interest rate swap contract information.
**MarketDataPublisher** publishes components of swap curves that include Deposits, FRAs and Swaps.
**Two calculators** subscribe to swap contract information and market data, reprice received swaps against the latest market data and republish priced portfolio of swaps to **clients.**

![http://qldds.googlecode.com/git/misc/IRS.jpg](http://qldds.googlecode.com/git/misc/IRS.jpg)

[InstrumentPublisher](https://code.google.com/p/qldds/source/browse/Examples/InterestRateSwaps/InstrumentDataPublisher.cpp) publishes contract information at a rate of 100 contracts per second.  Swap contract information consists of schedule::qlSchedule and vanillaswap::qlVanillaSwap QLDDS data types.   Upon publishing each of the samples of a given data type, publisher waits for an acknowledgement from each of the subscribers/IRSCalculators.

[MarketDataPublisher](https://code.google.com/p/qldds/source/browse/Examples/InterestRateSwaps/MarketDataPublisher.cpp) continuously publishes updates on the instrument components of a swap curve that include samples of ratehelpers::qlDepositRateHelper2, ratehelpers::qlFraRateHelper2 and  ratehelpers::qlSwapRateHelper2 QLDDS data types.

[IRSCalculators](https://code.google.com/p/qldds/source/browse/Examples/InterestRateSwaps/IRSCalculator.cpp) subscribe to all listed above data types. Once per second, they reprice received interest rate swaps against the specified in command line curve. Priced interest rate swaps are subsequently published in form of a portfolio to three clients.

[Clients](https://code.google.com/p/qldds/source/browse/Examples/InterestRateSwaps/IRSClient.cpp) subscribe to priced swap portfolio data and display portfolio NPVs on the screen.

## Topics: ##

| **Topic Name** | **TopicType** | **Source** | **Destination** |
|:---------------|:--------------|:-----------|:----------------|
|SCHEDULE\_TOPIC|schedule::qlSchedule|InstrumentDataPublisher|IRSCalculators|
|VANILLA\_SWAP\_TOPIC|vanillaswap::qlVanillaSwap|InstrumentDataPublisher|IRSCalculators|
|DEPOSIT\_RATE\_HELPER2\_TOPIC|ratehelpers::qlDepositRateHelper2|MarketDataPublisher|IRSCalculators|
|FRA\_RATE\_HELPER2\_TOPIC|ratehelpers::qlFraRateHelper2|MarketDataPublisher|IRSCalculators|
|SWAP\_RATE\_HELPER2\_TOPIC|ratehelpers::qlSwapRateHelper2|MarketDataPublisher|IRSCalculators|
|IRS\_PORTFOLIO\_TOPIC|IRS::Portfolio|IRSCalculator|Client|

## Configuring and Compiling: ##
### Unix: ###
```
$ $ACE_ROOT/bin/mwc.pl -type gnuace InterestRateSwaps.mwc 
$ make
```

### Windows(Visual Studio Command Prompt 2008): ###
```
> %ACE_ROOT%\bin\mwc.pl -type vc9 InterestRateSwaps_vc9.mwc 
> msbuild.exe InterestRateSwaps_vc9.sln
```


### Start scripts: ###

```
Unix : run_test.pl
Windows : run_test.bat
```