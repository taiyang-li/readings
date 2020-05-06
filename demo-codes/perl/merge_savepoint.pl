#!/usr/bin/perl

sub read_savepoint
{
	my $file = shift;
	my $sp;

	if (!open(FILE, "<$file"))
	{
		$sp = 0;
		return $sp;
	}

	while(<FILE>)
	{
		chomp;
		$sp = $_;
	}
	return $sp;
}

sub merge_single_savepoint
{
	my $spfile1 = shift;
	my $spfile2 = shift;
	
	my $sp1 = read_savepoint($spfile1);
	my $sp2 = read_savepoint($spfile2);
	print "sp1: $sp1, sp2: $sp2\n";

	return $sp1 >= $sp2 ? $sp2 : $sp1; 
}

sub merge_mutiple_savepoint
{
	my $sppath1 = shift;
	my $sppath2 = shift;
	my $retpath = "retpath";

	my $db_num = 32;
	my $tbl_num = 32;

	my $ret = system("mkdir $retpath");
	if ($ret < 0)
	{
		system("rm -rf ./$retpath")
	}

	my $i;
	my $j;
	for ($i=1; $i<=$db_num; $i++)
	{
		for ($j=1; $j<=$tbl_num; $j++)
		{
			my $spfile1 = sprintf("$sppath1/${sppath1}_%02d%02d", $i, $j);
			my $spfile2 = sprintf("$sppath2/${sppath2}_%02d%02d", $i, $j);
			my $retfile = sprintf("$retpath/${sppath1}_%02d%02d", $i, $j);
			print "merge $spfile1 and $spfile2 to $retfile\n";
			my $sp = merge_single_savepoint($spfile1, $spfile2);

			if (!open(FILE, ">$retfile"))
			{
				next;
			}

			print FILE $sp;
			close(FILE);
		}
	}
}

my $block_path = "block_listener";
my $grabrank_path = "grabrank_listener";
merge_mutiple_savepoint($block_path, $grabrank_path);



