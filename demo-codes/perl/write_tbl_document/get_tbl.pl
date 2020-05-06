#!/usr/bin/perl

use strict;

my $input_file = $ARGV[0];
my $output_file = $ARGV[1];

open(INPUT, "<$input_file") || die("open input file failed");
open(OUTPUT, ">$output_file") || die("open output file failed");

while (<INPUT>)
{
	chomp;
	if (m/(.*)\.xml.*tbl="(\d+)"/)
	{
		print OUTPUT  "$1\t$2\n";
	}
}

close(INPUT);
close(OUTPUT);
