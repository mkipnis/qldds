start %DDS_ROOT%\bin\DCPSInfoRepo -ORBEndpoint iiop://localhost:12345

ping localhost -n 1 -w 10000 > nul

start EquityOptionsServer.exe -DCPSConfigFile dds_tcp_conf.ini -s AAA
start EquityOptionsServer.exe -DCPSConfigFile dds_tcp_conf.ini -s BBB
start EquityOptionsServer.exe -DCPSConfigFile dds_tcp_conf.ini -s CCC

ping localhost -n 1 -w 10000 > nul

start EquityOptionsClient.exe -DCPSConfigFile dds_tcp_conf.ini 
start EquityOptionsClient.exe -DCPSConfigFile dds_tcp_conf.ini 

ping localhost -n 1 -w 10000 > nul

start DataPublisher.exe -DCPSConfigFile dds_tcp_conf.ini 


