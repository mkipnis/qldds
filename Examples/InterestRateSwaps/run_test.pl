eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

use Env qw(ACE_ROOT DDS_ROOT QLDDS_ROOT);
use lib "$DDS_ROOT/bin";
use lib "$ACE_ROOT/bin";
use PerlDDS::Run_Test;
#use strict;
my $status = 0;
my $failed = 0;

PerlACE::add_lib_path("$QLDDS_ROOT/lib");

my $repo_ior = PerlACE::LocalFile ("repo.ior");

my $dds_ini  = "dds_tcp_conf.ini";

# Change how test is configured according to which test we are.
my $repo_opts      = "-ORBEndpoint iiop://localhost:12345";
my $opts	   = "-DCPSConfigFile $dds_ini -m 0";

my $arg_ns_ref = "-ORBLogFile debug.log -ORBDebugLevel 1";
my $repo_args        = "$repo_opts";
my $args   = "$opts";

my $REPO;
my $MARKET_DATA_PUBLISHER;
my $INSTRUMENT_DATA_PUBLISHER;
my $IRS_CALCULATOR_1;
my $IRS_CALCULATOR_2;

my %orbsvcs = PerlDDS::orbsvcs ();
$REPO        = PerlDDS::create_process ("$ENV{DDS_ROOT}/bin/DCPSInfoRepo", $repo_args);

unlink $repo_ior;

# Fire up the repository.
print $REPO->CommandLine(), "\n";
$REPO->Spawn ();
if (PerlACE::waitforfile_timed ($repo_ior, 30) == -1) {
    print STDERR "ERROR: waiting for repository IOR file\n";
    $REPO->Kill ();
    exit 1;
}

sleep(1);

my $curveA = "Deposit/1M|Deposit/3M|FRA/6M9|FRA/6M12|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|";

# Start Calculator 1
my $args_a = "$args -n depot-fra-swap -c $curveA -ORBLogFile curve_a_calculator.log -ORBDebugLevel 10";
$IRS_CALCULATOR_1  = PerlDDS::create_process ("IRSCalculator", $args_a);
print $IRS_CALCULATOR_1->CommandLine(), "\n";
$IRS_CALCULATOR_1->Spawn ();

sleep(1);

my $curveB = "Deposit/1M|Deposit/3M|Deposit/6M|Deposit/1Y|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|";

# Start Calculator 2
my $args_b = "$args -n depo-swap -c $curveB -ORBLogFile curve_b_calculator.log -ORBDebugLevel 1";
$IRS_CALCULATOR_2  = PerlDDS::create_process ("IRSCalculator", $args_b);
print $IRS_CALCULATOR_2->CommandLine(), "\n";
$IRS_CALCULATOR_2->Spawn ();

sleep(1);

# Start Client 1
my $args_1 = "$args -i Client_1 -ORBLogFile client_1.log -ORBDebugLevel 1";
$IRS_CLIENT_1  = PerlDDS::create_process ("IRSClient", $args_1);
print $IRS_CLIENT_1->CommandLine(), "\n";
$IRS_CLIENT_1->Spawn ();

# Start Client 2
my $args_2 = "$args -i Client_2 -ORBLogFile client_2.log -ORBDebugLevel 1";
$IRS_CLIENT_2  = PerlDDS::create_process ("IRSClient", $args_2);
print $IRS_CLIENT_2->CommandLine(), "\n";
$IRS_CLIENT_2->Spawn ();

# Start Client 3 
my $args_3 = "$args -i Client_3 -ORBLogFile client_3.log -ORBDebugLevel 1";
$IRS_CLIENT_3  = PerlDDS::create_process ("IRSClient", $args_3);
print $IRS_CLIENT_3->CommandLine(), "\n";
$IRS_CLIENT_3->Spawn ();

sleep(1);

# Start Market Data Publisher
my $args_md = "$args -ORBLogFile market_data_publisher.log -ORBDebugLevel 1";
$MARKET_DATA_PUBLISHER = PerlDDS::create_process ("MarketDataPublisher", $args_md);
print $MARKET_DATA_PUBLISHER->CommandLine(), "\n";
$MARKET_DATA_PUBLISHER->Spawn ();

sleep(1);

# Start Instrument Data Publisher
my $ins_md = "$args -ORBLogFile instrument_data_publisher.log -ORBDebugLevel 1";
$INSTRUMENT_DATA_PUBLISHER = PerlDDS::create_process ("InstrumentDataPublisher", $ins_md);
print $INSTRUMENT_DATA_PUBLISHER->CommandLine(), "\n";
$INSTRUMENT_DATA_PUBLISHER->Spawn ();

# Wait up to 60 seconds for test to complete.
$status = $MARKET_DATA_PUBLISHER->WaitKill (60);
if ($status != 0) {
    print STDERR "ERROR: Market Data Publisher returned $status\n";
}
$failed += $status;

print "Market Data Publisher Exit Status : $status\n";

$status = $INSTRUMENT_DATA_PUBLISHER->WaitKill (5);
if ($status != 0) {
    print STDERR "ERROR: Market Data Publisher 2 returned $status\n";
}
$failed += $status;

print "Instrument Data Publisher Exit Status : $status\n";

$status = $IRS_CALCULATOR_1->WaitKill (5);
if ($status != 0) {
    print STDERR "ERROR: Subscriber 1 returned $status\n";
}
$failed += $status;

print "IRS Calculator 1 Exit Status : $status\n";

$status = $IRS_CALCULATOR_2->WaitKill (5);
if ($status != 0) {
    print STDERR "ERROR: Subscriber 2 returned $status\n";
}
$failed += $status;

print "IRS Calculator 2 Exit Status : $status\n";

$IRS_CLIENT_1->TerminateWaitKill(5);
$IRS_CLIENT_2->TerminateWaitKill(5);
$IRS_CLIENT_3->TerminateWaitKill(5);

$status = $REPO->TerminateWaitKill(5);
if ($status != 0) {
    print STDERR "ERROR: Repository returned $status\n";
}
$failed += $status;

print "Repo Exit Status : $status\n";

# Report results.

if ($failed == 0) {
  print "test PASSED.\n";
}
else {
  print STDERR "test FAILED.\n";
}
