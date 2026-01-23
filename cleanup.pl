#!/usr/bin/perl
use 5.30.0;
use warnings FATAL => 'all';
use autodie;

my @courses = qw(cs2470 cs3221 cs4310); # gd4000 cs4760);

for my $course (@courses) {
    my @dirs = `find "$course" -type d`;
    for my $dir (@dirs) {
        if (-e "$dir/pom.xml") {
            system(qq{(cd "$dir" && mvn clean)});
        }

        if ($dir =~ /\.git$/) {
            die("Stray .git: $dir\n");
        }
    }

    my @paths = `find "$course" -type f`;
    for my $path (@paths) {
        chomp $path;
        my $type = `file "$path"`; 
        if ($type =~ /ELF 64-bit/ || $type =~ /compiled Java class data/) {
            say("[$path] $type"); 
            if (length($path) > 5) {
                system(qq{rm -v "$path"});
            }
        }
    }
}
