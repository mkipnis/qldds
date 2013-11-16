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

my $dds_ini  = "dds_tcp_conf.ini";

# Change how test is configured according to which test we are.
my $repo_opts      = "-ORBEndpoint iiop://localhost:12345";
my $opts	   = "-DCPSConfigFile $dds_ini -m 0";
my $args   = "$common_opts $opts $arg_ns_ref";

@symbol = ("AAA","BBB","CCC");

my $REPO;
my $DATA_PUBLISHER;
my $PRICING_SERVER;
my $CLIENT;

my %orbsvcs = PerlDDS::orbsvcs ();
$REPO        = PerlDDS::create_process ("$ENV{DDS_ROOT}/bin/DCPSInfoRepo", $repo_opts);

unlink $repo_ior;

# Repository.
print $REPO->CommandLine(), "\n";
$REPO->Spawn ();
if (PerlACE::waitforfile_timed ($repo_ior, 30) == -1) {
    print STDERR "ERROR: waiting for repository IOR file\n";
    $REPO->Kill ();
    exit 1;
}

my $server_count = 0;

foreach ( @symbol )
{
  print $_;
  
  my $server_args = "$args -s $_";

  # Option Pricing Servers 
  $PRICING_SERVER[$server_count]  = PerlDDS::create_process ("EquityOptionsServer", $server_args);
  print $PRICING_SERVER[$server_count]->CommandLine(), "\n";
  $PRICING_SERVER[$server_count]->Spawn ();
  #select(undef, undef, undef, 0.1);
  sleep(1);

  $server_count++; 
}

sleep(1);

# Fire up the client
$CLIENT = PerlDDS::create_process ("EquityOptionsClient", $args);
print $CLIENT->CommandLine(), "\n";
$CLIENT->Spawn ();

sleep(1);

# Fire up the DataPublisher 
$DATA_PUBLISHER = PerlDDS::create_process ("DataPublisher", $args);
print $DATA_PUBLISHER->CommandLine(), "\n";
$DATA_PUBLISHER->Spawn ();

# Wait up to 10 seconds for test to complete.
$status = $DATA_PUBLISHER->WaitKill (60);
if ($status != 0) {
    print STDERR "ERROR: Subscriber 1 returned $status\n";
}
$failed += $status;

$CLIENT->TerminateWaitKill(1);

for( $server=0; $server<$server_count; $server++ )
{
  print "Killing Server [" + $server + "]\n";
  $status = $PRICING_SERVER[$server]->WaitKill (1);
  if ($status != 0) {
    print STDERR "ERROR: Subscriber 1 returned $status\n";
  }
  $failed += $status;
}

$status = $REPO->TerminateWaitKill(5);

# Report results.
if ($failed == 0) {
  print "test PASSED.\n";
}
else {
  print STDERR "test FAILED.\n";
}
