#!/usr/bin/perl -w 


# 读取输入文件 内容：报文字段
sub get_fields
{
	my $filepath = shift @_;
	my $fields;
	
	open(FILE, "<$filepath") || die("open file $filepath failed");
	while (<FILE>)
	{	
		chomp;
		my $line = $_;	
		@fields = ($line =~ m/\[([\w"\\]+)\]/g);
		last;
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

		if ($line =~ m/^\s+`(\w+)`\s+([\w()]+)\s+.*COMMENT\s+'(.*)'/)
		{
			my $field = $1;
			my $type = $2;
			my $comment = $3;
			my $type_comment = $type . "\t" . $comment;
			$field_type_comment_map{$field} = $type_comment;
		}
	}
	close(FILE);
	return %field_type_comment_map;
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
		if ($count == 1 || $count == 2)
		{
			print FILE "【$field】";
			print "【$field】";
			if ($count == 2)
			{
				print FILE "\n";
				print "\n";
			}
			next;
		}

		if (! exists($$field_type_comment_map{$field}))
		{
			print FILE "【$field】";
			print "【$field】";
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
my $type_comment_file = "type_comment";
my @fields;
my %field_type_comment_map;

@fields = get_fields($field_file);
%field_type_comment_map = get_type_comment($type_comment_file);
merge_field_with_typecomment(\%field_type_comment_map, \@fields);




