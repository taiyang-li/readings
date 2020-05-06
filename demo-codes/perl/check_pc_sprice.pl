#!/usr/bin/perl
use strict;

my $sprice = "/data/liyang/pcsprice.20151123";
# my $sprice = "log";
open(INPUT, "<$sprice") || die("open file $sprice failed");

my $line_no = 0;
while (<INPUT>)
{
	chomp;
	my $line = $_;
	$line_no++;
	# if ($line !~ /^([\x80-\xFF][\x80-\xFF]|\w| |\/)+\x03\d+\x03\d+$/)
	if ($line !~ /^[^\x03\n]+\x03\d+\x03\d+$/)
	{
		print $line_no, "\t\t";
		print $line;
		print "\n";
	}
}
close(INPUT);

