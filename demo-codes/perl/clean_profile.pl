#!/usr/bin/perl
use strict;
use Set::Scalar; 

open (INPUT, "< /root/.bash_profile") || die("open input file failed");
open (OUTPUT, "> /root/.bash_profile.bak") || die("open output file failed"); 

my $s = Set::Scalar->new;
while(<INPUT>)
{
	chomp;
	my $line = $_;
	if ($line =~ /^export\s+.*=.*/)
	{
		$s->insert($line);
	}
	else
	{
		print OUTPUT $line;
		print OUTPUT "\n";
	}
}


while (defined(my $e = $s->each)) 
{
	print OUTPUT $e;	
	print OUTPUT "\n";
}

close INPUT;
close OUTPUT;
