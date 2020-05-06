#!/usr/bin/perl
use strict;
use Time::Local;

sub string2time;
my $input_file = $ARGV[0];
my $output_file = $input_file . ".delay";


print "input_file: ", $input_file, "\n";
print "output_file: ", $output_file, "\n";

open(INPUT, "<$input_file") ||die("open input file failed");
open(OUTPUT, ">$output_file") || die("open output file failed");

my $time;
my $cur_time;
my $delay_sec;
my $max_delay = 0;
my $str_time;
my $str_cur_time;
while(<INPUT>)
{
	chomp;
	if (m/sendlist(\w+)\x05/)
	{
		my $topic = $1;

		#if ($topic eq "cpc" || $topic eq "cpcgrp" || 
		#		$topic eq "cpcplan" || $topic eq "account" ||
		#		$topic eq "cpcidea" || $topic eq "extraidea")
		if ($topic eq "cpcgrp" || $topic eq "cpcplanlevel" || $topic eq "cpcaccountlevel")
		{
			# $_ = "2015-12-02 19:00:01";
			if (m/(\d+-\d+-\d+\s+\d+:\d+:\d+)(\x05.*)$/)
			{
				$str_time = $1;
				$time = string2time($1);
				if (m/^\[(\d+-\d+-\d+ \d+:\d+:\d+)/)
				{
					$str_cur_time = $1;
					$cur_time = string2time($1);
				}
				$delay_sec = $cur_time - $time;
				$max_delay = $delay_sec if ($delay_sec > $max_delay);
				print OUTPUT "$str_time\t$str_cur_time\t$delay_sec\n";
				print "$str_time\t$str_cur_time\t$delay_sec\n";
			}
		}
	}
}

print "max_delay: " . $max_delay;
print OUTPUT $max_delay;
close(INPUT);
close(OUTPUT);

sub string2time
{
	my $string = shift;
	if ($string =~ m/(\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2})/)
	{
			
		my ($sec, $min, $hour, $day, $mon, $year) = ($6, $5, $4, $3, $2-1, $1-1900);
		my $time = timelocal($sec, $min, $hour, $day, $mon, $year);
		return $time;
	}
	return 0;

}

