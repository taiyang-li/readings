#!/usr/bin/perl -w

# 将数据库中big_account_table表中hades server字段中数据
# 从 hades.1.4.server --> hades.1.1.server
# 从 hades.1.5.server --> hades.1.2.server
# 从 hades.1.6.server --> hades.1.3.server

$input_file = "big_account_table.csv";
$output_file = "modified_big_account_table.csv";

open(IN_FILE, "<$input_file") || die("open input file $input_file failed");
open(OUT_FILE, ">$output_file") || die("open output file $output_file failed");

while(<IN_FILE>)
{
	chomp;
	my $line = $_;
	$line =~ s/"//g;

	if ($line =~ m/hades\.(\d+)\.(\d+)\.server\s+hades\.(\d+)\.(\d+)\.server/)
	{
		my $idx11 = $1;
		my $idx12 = $2;
		my $idx21 = $3;
		my $idx22 = $4;
		print "$idx11, $idx12, $idx21, $idx22";
		print "\n";
		
		if ($idx12 == 4 || $idx12 == 5 || $idx12 == 6)
		{
			$idx12 -= 3;
		}
		
		if ($idx22 == 4 || $idx22 == 5 || $idx22 == 6)
		{
			$idx22 -= 3;
		}

		$line =~ s/hades.*hades\.\d+\.\d+\.server/hades\.$idx11\.$idx12\.server hades\.$idx21\.$idx22\.server/;
		print OUT_FILE $line;
		print OUT_FILE "\n";
	}
	else
	{
		print OUT_FILE $line;
		print OUT_FILE "\n";
	}
}

close(IN_FILE);
close(OUT_FILE);




