eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

use Env (ACE_ROOT);
use Env (DDS_ROOT);
use lib "$ACE_ROOT/bin";
use lib "$DDS_ROOT/bin";
use PerlDDS::Run_Test;

my $status = 0;
my $failed = 0;

my $repo_ior = PerlACE::LocalFile ("repo.ior");
my $ns_ior   = PerlACE::LocalFile ("ns.ior");

my $dds_ini  = "dds_tcp_conf.ini";

# Change how test is configured according to which test we are.
my $repo_opts      = "-ORBEndpoint iiop://localhost:12345";
my $opts           = "-DCPSConfigFile $dds_ini";
my $args           = "$opts -ORBInitRef NameService=iiop://localhost:23456/NameService";

my $REPO;
my $SWAPTION_CLIENT;
my $MARKET_DATA_PUBLISHER;
my $SWAPTION_SERVER;

my %orbsvcs = PerlDDS::orbsvcs ();
$NS = PerlDDS::create_process ($orbsvcs{'Naming_Service'}, "-ORBListenEndpoints iiop://localhost:23456 -o $ns_ior -ORBDebugLevel 0");
$REPO        = PerlDDS::create_process ("$ENV{DDS_ROOT}/bin/DCPSInfoRepo", $repo_opts);

unlink $repo_ior;
unlink $ns_ior;

# Start TAO Naming Service
print $NS->CommandLine(), "\n";
$NS->Spawn();
if (PerlACE::waitforfile_timed ($ns_ior, 30) == -1) {
    print STDERR "ERROR: cannot find file <$ns_ior>\n";
    $NS->Kill();
    exit 1;
}

# Start OpenDDS Repo 
print $REPO->CommandLine(), "\n";
$REPO->Spawn ();
if (PerlACE::waitforfile_timed ($repo_ior, 30) == -1) {
    print STDERR "ERROR: waiting for repository IOR file\n";
    $REPO->Kill ();
    exit 1;
}

sleep(1);

# Start Swaption Server 1
$args_swaption_server1 = "$args -ORBLogFile swaptions_server1.log -ORBDebugLevel 10 -s SwaptionServer1";
$SWAPTION_SERVER1  = PerlDDS::create_process ("SwaptionServer", $args_swaption_server1);
print $SWAPTION_SERVER1->CommandLine(), "\n";
$SWAPTION_SERVER1->Spawn ();

sleep(1);

# Start Swaption Server 2
$args_swaption_server2 = "$args -ORBLogFile swaptions_server2.log -ORBDebugLevel 10 -s SwaptionServer2";
$SWAPTION_SERVER2  = PerlDDS::create_process ("SwaptionServer", $args_swaption_server2);
print $SWAPTION_SERVER2->CommandLine(), "\n";
$SWAPTION_SERVER2->Spawn ();

sleep(1);

# Start Market Data Publisher
$args_market_data_publisher = "$args -ORBLogFile market_data_publisher.log -ORBDebugLevel 1";
$MARKET_DATA_PUBLISHER  = PerlDDS::create_process ("MarketDataPublisher", $args_market_data_publisher);
print $MARKET_DATA_PUBLISHER->CommandLine(), "\n";
$MARKET_DATA_PUBLISHER->Spawn ();

sleep(1);

$curve = "Deposit/1M|Deposit/3M|FRA/6M9|FRA/6M12|Swap/2Y|Swap/5Y|Swap/10Y|Swap/15Y|Swap/50Y|";

$args_client = "$args -ORBLogFile swaptions_client.log -c $curve";
$SWAPTION_CLIENT  = PerlDDS::create_process ("Client", $args_client);
print $SWAPTION_CLIENT->CommandLine(), "\n";
$SWAPTION_CLIENT->Spawn ();

# Wait up to 30 seconds for test to complete.
$status = $SWAPTION_SERVER1->WaitKill (30);
if ($status != 0) {
    print STDERR "ERROR: Swaption Server returned $status\n";
}
$failed += $status;

print "Swaption Server 1: $status\n";

# Wait up to 5 seconds for test to complete.
$status = $SWAPTION_SERVER2->WaitKill (5);
if ($status != 0) {
    print STDERR "ERROR: Swaption Server returned $status\n";
}
$failed += $status;

print "Swaption Server 2: $status\n";

# Wait up to 1 seconds for test to complete.
$status = $SWAPTION_CLIENT->WaitKill (1);
if ($status != 0) {
    print STDERR "ERROR: Client returned $status\n";
}
$failed += $status;

print "Swaption Client : $status\n";

# Wait up to 1 seconds for test to complete.
$status = $MARKET_DATA_PUBLISHER->WaitKill (1);
if ($status != 0) {
    print STDERR "ERROR: Market Data Publisher returned $status\n";
}
$failed += $status;

print "MarketDataPublisher : $status\n";

$status = $NS->TerminateWaitKill(5);
if ($status != 0) {
    print STDERR "ERROR: NamingService returned $status\n";
}
$failed += $status;

$status = $REPO->TerminateWaitKill(5);
if ($status != 0) {
    print STDERR "ERROR: Repository returned $status\n";
} 
$failed += $status;

print "Repo Exit Status : $status\n";

if ($failed == 0) {
  print "test PASSED.\n";
}
else {
  print STDERR "test FAILED.\n";
}
