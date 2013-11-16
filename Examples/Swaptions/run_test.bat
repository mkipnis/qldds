start %DDS_ROOT%\bin\DCPSInfoRepo -ORBEndpoint iiop://localhost:12345

start %ACE_ROOT%\TAO\orbsvcs\Naming_Service\.\Naming_Service.EXE -ORBListenEndpoints iiop://localhost:23456 -o ns.ior

ping localhost -n 1 -w 10000 > nul

start SwaptionServer.EXE -DCPSConfigFile dds_tcp_conf.ini -ORBInitRef NameService=iiop://localhost:23456/NameService -ORBLogFile swaptions_server.log -s SwaptionServer1

start SwaptionServer.EXE -DCPSConfigFile dds_tcp_conf.ini -ORBInitRef NameService=iiop://localhost:23456/NameService -ORBLogFile swaptions_server.log -s SwaptionServer2

start MarketDataPublisher.exe -DCPSConfigFile dds_tcp_conf.ini 

ping localhost -n 1 -w 10000 > nul

start Client.EXE -DCPSConfigFile dds_tcp_conf.ini -ORBInitRef NameService=iiop://localhost:23456/NameService -ORBLogFile swaptions_client.log -c "Deposit/1M|Deposit/3M|FRA/6M9|FRA/6M12|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|"
