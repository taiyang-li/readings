#!/usr/bin/perl -w

# 根据数据直接生成sql语句

$input_file = "modified_big_account_table.csv";
$output_file = "import.sql";

open(IN_FILE, "<$input_file") || die("open input file $input_file failed");
open(OUT_FILE, ">$output_file") || die("open output file $output_file failed");

# 删除mysql中big_account_table表
print OUT_FILE "delete from big_account_table";
print OUT_FILE ";\n";

while (<IN_FILE>)
{
	chomp;
	my $line = $_;	
	if ($line =~ m/(\d+),(hade.*hades.*.server),(\d+),(\d+)/)
	{
		my $cpcid = $1;
		my $hades_server = $2;
		my $count = $3;
		my $consume = $4;

		my $sql;
		$sql = "insert into `big_account_table` (`ACCOUNTID`, `HADESNAME`, `COUNT`, `CONSUME`, `CHG_DATE`) values";
		$sql = $sql . "($cpcid, '$hades_server', $count, $consume, now())";
		print OUT_FILE $sql;
		print OUT_FILE ";\n";
	}
}

close(IN_FILE);
close(OUT_FILE);
