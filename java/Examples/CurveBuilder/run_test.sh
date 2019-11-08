#!/bin/bash

set -x


trap cleanup 1 2 3 6

cleanup()
{
  echo "Caught Signal ... cleaning up."
  kill $CURVE_BUILER_CLIENT_PID
  kill $CURVE_BUILDER_PID

  kill $REPO_PID

  echo "Done cleanup ... quitting."
  exit 1
}


CWD=`pwd`

export LD_LIBRARY_PATH=$QLDDS_ROOT/java/lib:$CWD/CurveBuilderIDL:$DDS_ROOT/java/dds:$LD_LIBRARY_PATH:

echo "Current working directory : " + $CWD

$DDS_ROOT/bin/DCPSInfoRepo -o repo.ior -ORBEndpoint iiop://localhost:12345&
REPO_PID=$!

sleep 1

COMMON_OPTS="-DCPSConfigFile tcp.ini"

echo $COMMON_OPTS

$CWD/Server/CurveBuilder $COMMON_OPTS -ORBLogFile CurveBuilder.log -ORBDebugLevel 1 &
CURVE_BUILDER_PID=$!

java -cp $DDS_ROOT/lib/OpenDDS_DCPS.jar:$DDS_ROOT/lib/i2jrt.jar:tao_jar:$QLDDS_ROOT/java/lib/ratehelpers.jar:$QLDDS_ROOT/java/lib/piecewiseyieldcurve.jar:$QLDDS_ROOT/java/Examples/CurveBuilder/CurveBuilderIDL/CurveBuilder.jar:$QLDDS_ROOT/java/lib/qldds_utils_java.jar:$QLDDS_ROOT/java/Examples/CurveBuilder/Client/classes Client $COMMON_OPTS -ORBLogFile CurveBuilderClient.log -ORBDebugLevel 1&
CURVE_BUILDER_CLIENT_PID=$1

sleep 10

kill $CURVE_BUILER_CLIENT_PID

kill $CURVE_BUILDER_PID

kill $REPO_PID
