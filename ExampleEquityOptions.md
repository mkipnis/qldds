# Equity Options #
## Scenario: ##

[DataPublisher](https://code.google.com/p/qldds/source/browse/Examples/EquityOptions/EquityOptionsDataPublisher.cpp) publishes indicative and market data information for 20 put and call strikes for three stock tickers. [Three calculators(EquityOptionServers)](https://code.google.com/p/qldds/source/browse/Examples/EquityOptions/EquityOptionsServer.cpp) subscribe to indicative and market data for a given stock ticker. They compute NPVs and Greeks on puts and calls of received strikes and publish results to clients.  [Client](https://code.google.com/p/qldds/source/browse/Examples/EquityOptions/EquityOptionsClient.cpp) receives data published by 3 calculators and display the results.

This example also demonstrates the multi-topic subscription feature of OpenDDS by having sequences of BlackContantVols, GeneralizedBlackScholesProcesses, StickedTypePayoffs and EuropeanExcercises published by the DataPublisher and joined on the ticker by the EquityOptionServer.

![https://qldds.googlecode.com/git/misc/EquityOptions.jpg](https://qldds.googlecode.com/git/misc/EquityOptions.jpg)

## Topics: ##

## Configuring and Compiling: ##
### Unix: ###
```
$ $ACE_ROOT/bin/mwc.pl -type gnuace EquityOptions.mwc 
$ make
```

### Windows(Visual Studio Command Prompt 2008): ###
```
> %ACE_ROOT%\bin\mwc.pl -type vc9 EquityOptions_vc9.mwc 
> msbuild.exe EquityOptions_vc9.sln
```

### Start scripts: ###
```
Unix : run_test.pl
Windows : run_test.bat
```