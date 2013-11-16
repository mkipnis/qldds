start %DDS_ROOT%\bin\DCPSInfoRepo -ORBEndpoint iiop://localhost:12345

ping localhost -n 1 -w 10000 > nul

start IRSCalculator.EXE  -DCPSConfigFile dds_tcp_conf.ini -m 0 -n depot-fra-swap -c "Deposit/1M|Deposit/3M|FRA/6M9|FRA/6M12|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|" -ORBLogFile curve_a_calculator.log -ORBDebugLevel 10
start IRSCalculator.EXE  -DCPSConfigFile dds_tcp_conf.ini -m 0 -n depo-swap -c "Deposit/1M|Deposit/3M|Deposit/6M|Deposit/1Y|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|" -ORBLogFile curve_b_calculator.log -ORBDebugLevel 1

ping localhost -n 1 -w 10000 > nul

start IRSClient.EXE  -DCPSConfigFile dds_tcp_conf.ini -m 0 -i Client_1 -ORBLogFile client_1.log -ORBDebugLevel 1
start IRSClient.EXE  -DCPSConfigFile dds_tcp_conf.ini -m 0 -i Client_2 -ORBLogFile client_2.log -ORBDebugLevel 1
start IRSClient.EXE  -DCPSConfigFile dds_tcp_conf.ini -m 0 -i Client_3 -ORBLogFile client_3.log -ORBDebugLevel 1

ping localhost -n 1 -w 10000 > nul

start InstrumentDataPublisher.EXE  -DCPSConfigFile dds_tcp_conf.ini -m 0 -ORBLogFile instrument_data_publisher.log -ORBDebugLevel 1

start MarketDataPublisher.EXE  -DCPSConfigFile dds_tcp_conf.ini -m 0 -ORBLogFile market_data_publisher.log -ORBDebugLevel 1
