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

my $dds_ini  = "../tcp.ini";

# Change how test is configured according to which test we are.
my $repo_opts      = "-ORBEndpoint iiop://localhost:12345";
my $opts	   = "-DCPSConfigFile $dds_ini -m 0";

my $arg_ns_ref = "-ORBLogFile debug.log -ORBDebugLevel 1";
my $repo_args        = "$common_opts $repo_opts";
my $args   = "$common_opts $opts";

my $REPO;
my $CURVE_BUILDER;

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

# Start CurveBuilder
my $args_a = "$args -ORBLogFile curve_builder.log -ORBDebugLevel 10";
$CURVE_BUILDER  = PerlDDS::create_process ("CurveBuilder", $args_a);
print $CURVE_BUILDER->CommandLine(), "\n";
$CURVE_BUILDER->Spawn ();

sleep(1);

$status = $CURVE_BUILDER->WaitKill (5);
if ($status != 0) {
    print STDERR "ERROR: Subscriber 1 returned $status\n";
}
$failed += $status;

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
