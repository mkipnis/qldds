#!/bin/bash

set -x


trap cleanup 1 2 3 6

cleanup()
{
  echo "Caught Signal ... cleaning up."
  kill $DATA_PUBLISHER_PID

  kill $EQUITY_OPTION_SERVER_AAA_PID
  kill $EQUITY_OPTION_SERVER_BBB_PID
  kill $EQUITY_OPTION_SERVER_CCC_PID

  kill $CLIENT_PID

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

$CWD/EquityOptionsClient $COMMON_OPTS -ORBLogFile client.log -ORBDebugLevel 1 &
CLIENT_PID=$!

sleep 1

$CWD/EquityOptionsServer $COMMON_OPTS -s AAA -ORBLogFile curve_AAA_calculator.log -ORBDebugLevel 10 &
EQUITY_OPTION_SERVER_AAA_PID=$!

$CWD/EquityOptionsServer $COMMON_OPTS -s BBB -ORBLogFile curve_BBB_calculator.log -ORBDebugLevel 10 &
EQUITY_OPTION_SERVER_BBB_PID=$!


$CWD/EquityOptionsServer $COMMON_OPTS -s CCC -ORBLogFile curve_CCC_calculator.log -ORBDebugLevel 10 &
EQUITY_OPTION_SERVER_CCC_PID=$!

sleep 1

$CWD/DataPublisher $COMMON_OPTS -ORBLogFile data_publisher.log -ORBDebugLevel 10 &
DATA_PUBLISHER_PID=$!

sleep 10

kill $DATA_PUBLISHER_PID

kill $EQUITY_OPTION_SERVER_AAA_PID
kill $EQUITY_OPTION_SERVER_BBB_PID
kill $EQUITY_OPTION_SERVER_CCC_PID

kill $CLIENT_PID

kill $REPO_PID
