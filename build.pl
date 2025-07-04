#!/usr/bin/perl

use File::Path qw(make_path);

my $SRC_DIR = "src";
my $CC = "gcc";

make_path($SRC_DIR);

system("$CC $SRC_DIR/fat12.c src/main.c");
