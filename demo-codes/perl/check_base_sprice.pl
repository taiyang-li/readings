#!/usr/bin/perl
use strict;

my $dir = "D:\\data";
open (OUTPUT, ">dirty_data") || die ("open output file failed\n");

my @files = glob "extraidea*";
print @files;

foreach my $file (@files)
{
	print "open file $file\n";
	open (INPUT, "<$file") || die("open input file $file failed\n");
	while (<INPUT>)
	{
		chomp;
		if (m/cdn\.sogou\.com/)
		{
			print $_, "\n";
			print OUTPUT "$_\n"; 
		}
	}
	close(INPUT);
	print "close file $file\n";
}
close(OUTPUT);

