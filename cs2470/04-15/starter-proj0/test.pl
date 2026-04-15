#!/usr/bin/perl
use 5.16.0;
use warnings FATAL => 'all';

use Test::Simple tests => 12;

ok(!-e "./nush", "no binary");

system("(make 2>&1) > /dev/null");

system("rm -rf tmp");
system("mkdir -p tmp");

my @scripts = glob("tests/*.sh");

for my $script (@scripts) {
    system("rm -f tmp/output");
    system("timeout -k 5 10 ./nush $script > tmp/output");

    my $correct = $script;
    $correct =~ s/\.sh$/.out/;
    my $diff = `diff $correct tmp/output`;

    ok($diff eq "", $script);
    if ($diff ne "") {
        $diff =~ s/^/# /mg;
        print $diff;
    }
}

my @outs = qw(output sample.txt sorted2.txt sorted.txt);
for my $out (@outs) {
    ok(-e "tmp/$out", "expected output exists: $out");
}

# Verify sorted2.txt was created with correct content (catches missing O_CREAT bug)
my $sorted2_content = `cat tmp/sorted2.txt 2>/dev/null`;
my $expected_sorted = `sort tests/sample.txt`;
ok($sorted2_content eq $expected_sorted, "sorted2.txt has correct sorted content");

# Verify sorted.txt was created with correct content (sort -o test)
my $sorted_content = `cat tmp/sorted.txt 2>/dev/null`;
ok($sorted_content eq $expected_sorted, "sorted.txt has correct sorted content");

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
    my $errs = `clang-check -analyze *.c -- 2>&1`;
    return check_errors($errs);
}

sub valgrind() {
    system(qq{timeout -k 5 10 valgrind -q --leak-check=full --log-file=valgrind.out ./nush tests/01-echo.sh > main.out});
    return `cat -n valgrind.out` eq "";
}

ok(clang_check(), "clang check");
ok(valgrind(), "valgrind");

my $procs = `ps | grep memcheck`;
chomp $procs;

ok($procs eq "", "no stray processes after tests");
if ($procs ne "") {
    system("killall memcheck-amd64-");
}

system("(make clean 2>&1) > /dev/null");
