#!/bin/bash

set -x


trap cleanup 1 2 3 6

cleanup()
{
  echo "Caught Signal ... cleaning up."
  kill $CONTRACT_PUBLISHER
  kill $MARKET_DATA_PUBLISHER_PID

  kill $SWAPTION_SERVER_B_PID
  kill $SWAPTION_SERVER_A_PID

  kill $CLIENT_PID

  kill $REPO_PID
  kill $REPO_PID

  echo "Done cleanup ... quitting."
  exit 1
}


CWD=`pwd`

echo "Current working directory : " + $CWD

COMMON_OPTS="-DCPSConfigFile dds_tcp_conf.ini -ORBInitRef NameService=iiop://localhost:23456/NameService"

$DDS_ROOT/bin/DCPSInfoRepo -o repo.ior -ORBEndpoint iiop://localhost:12345&
REPO_PID=$!

$CWD/SwaptionServer $COMMON_OPTS -ORBLogFile swaptions_server1.log -ORBDebugLevel 10 -s SwaptionServer1 &
SWAPTION_SERVER_A_PID=$!

$CWD/SwaptionServer $COMMON_OPTS -ORBLogFile swaptions_server2.log -ORBDebugLevel 10 -s SwaptionServer2 &
SWAPTION_SERVER_B_PID=$!

$CWD/MarketDataPublisher $COMMON_OPTS  -ORBLogFile market_data_publisher.log -ORBDebugLevel 10&
MARKET_DATA_PUBLISHER_PID=$!

sleep 5

$CWD/Client $COMMON_OPTS -ORBDebugLevel 10  -ORBLogFile swaptions_client.log -c  "Deposit/1M|Deposit/3M|FRA/6M9|FRA/6M12|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|" &
CLIENT_PID=$!

sleep 10

kill $CLIENT_PID
kill $MARKET_DATA_PUBLISHER_PID

kill $SWAPTION_SERVER_B_PID
kill $SWAPTION_SERVER_A_PID

kill $REPO_PID
kill $NS_PID
