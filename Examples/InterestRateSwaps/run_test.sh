#!/bin/bash

set -x


trap cleanup 1 2 3 6

cleanup()
{
  echo "Caught Signal ... cleaning up."
  kill $CONTRACT_PUBLISHER
  kill $MARKET_DATA_PUBLISHER_PID

  kill $CALCULATOR_CURVE_B_PID
  kill $CALCULATOR_CURVE_A_PID

  kill $CLIENT_1_PID
  kill $CLIENT_2_PID

  kill $REPO_PID

  echo "Done cleanup ... quitting."
  exit 1
}


CWD=`pwd`

echo "Current working directory : " + $CWD

$DDS_ROOT/bin/DCPSInfoRepo -o repo.ior -ORBEndpoint iiop://localhost:12345&
REPO_PID=$!

sleep 1

COMMON_OPTS="-DCPSConfigFile dds_tcp_conf.ini"

echo $COMMON_OPTS

$CWD/IRSClient $COMMON_OPTS -i Client_1 -ORBLogFile client_1.log -ORBDebugLevel 1 &
CLIENT_1_PID=$!

$CWD/IRSClient $COMMON_OPTS -i Client_2 -ORBLogFile client_2.log -ORBDebugLevel 1 &
CLIENT_2_PID=$!

sleep 1

$CWD/IRSCalculator $COMMON_OPTS  -n depot-fra-swap -c "Deposit/1M|Deposit/3M|FRA/6M9|FRA/6M12|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|" -ORBLogFile curve_a_calculator.log -ORBDebugLevel 10 &
CALCULATOR_CURVE_A_PID=$!

$CWD/IRSCalculator $COMMON_OPTS  -n depot-swap -c "Deposit/1M|Deposit/3M|Deposit/6M|Deposit/1Y|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|" -ORBLogFile curve_b_calculator.log -ORBDebugLevel 10 &
CALCULATOR_CURVE_B_PID=$!

sleep 1

$CWD/MarketDataPublisher $COMMON_OPTS -ORBLogFile market_data_publisher.log -ORBDebugLevel 10 &
MARKET_DATA_PUBLISHER_PID=$!

$CWD/InstrumentDataPublisher $COMMON_OPTS -ORBLogFile contract_publisher.log -ORBDebugLevel 10 &
CONTRACT_PUBLISHER=$!

sleep 10

kill $CONTRACT_PUBLISHER
kill $MARKET_DATA_PUBLISHER_PID

kill $CALCULATOR_CURVE_B_PID
kill $CALCULATOR_CURVE_A_PID

kill $CLIENT_1_PID
kill $CLIENT_2_PID

kill $REPO_PID
