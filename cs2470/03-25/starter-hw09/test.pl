#!/usr/bin/perl
use 5.16.0;
use warnings FATAL => 'all';

use Test::Simple tests => 8;

my @objs = glob("*.o");
ok(!-e "calcpi" && scalar @objs == 0, "no binaries");

ok(-e "REPORT.md", "REPORT.md exists");

system("make 2>&1 > /dev/null");

my $out1 = `./calcpi 1`;
ok($out1 =~ /Calculating pi using 1 procs/, "output shows 1 proc");
ok($out1 =~ /With \d+ samples: π ≈ (\d+\.\d+)/ && $1 > 2.0 && $1 < 4.0, "pi is between 2 and 4 for 1 proc");

my $out4 = `./calcpi 4`;
ok($out4 =~ /Calculating pi using 4 procs/, "output shows 4 procs");
ok($out4 =~ /With \d+ samples: π ≈ (\d+\.\d+)/ && $1 > 2.0 && $1 < 4.0, "pi is between 2 and 4 for 4 procs");

my @temp_files = glob("/tmp/worker-*.dat");
ok(scalar @temp_files == 0, "temp files cleaned up");

sub check_errors {
    my ($errs) = @_;
    chomp $errs;
    if ($errs ne "") {
        $errs =~ s/^/# /mg;
        warn $errs;
        return 0;
    }
    else {
        return 1;
    }
}

sub clang_check {
    my $errs = `clang-check -analyze *.c -- 2>/dev/null`;
    return check_errors($errs);
}

ok(clang_check(), "clang check");

system("make clean 2>&1 > /dev/null");