#!/usr/bin/perl
use 5.16.0;
use warnings FATAL => 'all';

use Test::Simple tests => 15;
use IO::Handle;

my @objs = glob("*.o");
ok(!-e "tokens" && scalar @objs == 0, "no binaries");

system("make 2>&1 > /dev/null");

system("mkdir -p tmp");

my @scripts = glob("tests/*.sh");

for my $script (@scripts) {
    system("rm -f tmp/raw tmp/output");
    system("timeout 5 ./tokens < $script > tmp/raw");

    my $correct = $script;
    $correct =~ s/\.sh$/.out/;
    system("cp $correct tmp/expect");

    my $output = `cat tmp/raw`;
    $output =~ s/^\w+\$\s*//mg;
    open my $fh, ">", "tmp/output";
    $fh->print($output);
    close $fh;

    my $diff = `diff -B tmp/expect tmp/output`;

    ok($diff eq "", $script);
    if ($diff ne "") {
        $diff =~ s/^/# /mg;
        print $diff;
    }
}

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

sub valgrind {
    my ($cmd) = @_;
    my $vg = "valgrind -q --leak-check=full --log-file=valgrind.out";
    system(qq{timeout -k 10 10 $vg $cmd 2>&1 > /dev/null || true});
    my $errs = `cat -n valgrind.out`;
    check_errors($errs);
    return $errs eq "";
}

ok(valgrind(qq{./tokens < tests/05-sort-rin.sh}), "valgrind");

system("make clean 2>&1 > /dev/null");
