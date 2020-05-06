#!/usr/bin/perl -w 

# 读取输入文件 内容：报文字段
sub get_fields
{
	my $filepath = shift @_;
	my @fields;
	
	open(FILE, "<$filepath") || die("open file $filepath failed");
	while (<FILE>)
	{	
		chomp;
		my $line = $_;
		if ($line =~ m/table\s+name="(\w+)"/ )
		{
			push(@fields, $1);
		}
		elsif ($line =~ m/column\s+name="(\w+)"/)
		{
			push(@fields, $1);
		}
	}
	close(FILE);
	return @fields;
}

sub get_type_comment
{	
	my $filepath = shift @_;
	my %field_type_comment_map;
	
	open(FILE, "<$filepath") || die("open file $filepath failed");
	while (<FILE>)
	{
		chomp;
		my $line = $_;

		my $field;
		my $type;
		my $comment = "";
		my $type_comment;
		if ($line =~ m/^\s+`(\w+)`\s+([\w()]+)\s+/)
		# if ($line =~ m/^\s+`(\w+)`\s+([\w()]+)\s+.*COMMENT\s+'(.*)'/)
		{
			$field = $1;
			$type = $2;
			if ($line =~ m/COMMENT\s+'(.*)'/)
			{
				$comment = $1;
			}
			$type_comment = $type . "\t" . $comment;
			$field_type_comment_map{lc($field)} = $type_comment;
		}
	}
	close(FILE);
	return %field_type_comment_map;
}

sub write_field_to_file
{
	my $fields = shift @_;
	open(FILE, ">field_output_file") || die("open field output file failed");
	
	my $count = 0;
	my $number = @$fields;
	foreach my $field (@$fields)
	{
		$count++;

		if ($count == 1)
		{
			print FILE "$field \\5 OP \\5 ";
			print  "$field \\5 OP \\5 ";
		}
		elsif ($count != $number)
		{
			print FILE "$field \\3 ";
			print  "$field \\3 ";
		}
		else
		{
			print FILE "$field (\\5 chg_cols[0] \\3 chg_values[0] ...)";
			print  "$field (\\5 chg_cols[0] \\3 chg_values[0] ...)";
		}
	}
	close(FILE);
}

sub merge_field_with_typecomment
{
	my $field_type_comment_map = shift @_;
	my $fields = shift @_;
	
	open(FILE, ">output") || die("open file ouput failed");
	my $count = 0;
	foreach my $field (@$fields)
	{
		$count++;
		if ($count == 1)
		{
			next;
		}

		if (! exists($$field_type_comment_map{$field}))
		{
			print FILE "【$field】";
			print "【$field//】";
			print FILE "\n";
			print "\n";
			next;
		}

		my $type_comment = $$field_type_comment_map{$field};
		my $type;
		my $comment;
		if ($type_comment =~ m/^([\w()]+)\t(.*)$/)
		{
			$type = $1;
			$comment = $2;
		}
		
		print FILE "【" . $field . "/" . $type . "/" . $comment . "】"; 
		print "【" . $field . "/" . $type . "/" . $comment . "】"; 
		print FILE "\n";
		print "\n";
	}

	print "\n";
	close(FILE);
}

my $field_file = "field";
my $field_output_file = "field_output";
my $type_comment_file = "type_comment";
my @fields;
my %field_type_comment_map;

@fields = get_fields($field_file);
%field_type_comment_map = get_type_comment($type_comment_file);
merge_field_with_typecomment(\%field_type_comment_map, \@fields);
print "\n";
write_field_to_file(\@fields);





