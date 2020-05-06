#!/usr/bin/perl

use File::Basename;

sub clean_workspace
{	
	my $target_filelist = shift;
	my $ref_filelist = shift;

	my @target_filename = map basename($_), @$target_filelist;
	my @ref_filename = map basename($_), @$ref_filelist;
	
	my $target_dirname = dirname($$target_filelist[0]);
	my $ref_dirname = dirname($$ref_filelist[0]);

	foreach  $file (@target_filename)
	{
		if (is_in_list($file, \@ref_filename) == 0)
		{
			print "rm -rf $target_dirname/$file\n";
			print SHELL "rm -rf $target_dirname/$file\n";
		}
	}
}

sub is_in_list
{
	my $target = shift;
	my $list = shift;
	
	# Èç¹ûlistÎª¿Õ
	if (length(@$list) == 0)
	{
		return 1;
	}

	foreach $i (@$list)
	{
		if ($target eq $i)
		{
			return 1;
		}
	}
	return 0;
}

my $src_workspace = "/data/liyang/trunk/workspace";
my $release_workspace = "/data/liyang/trunk/build64_release/workspace";
my $debug_workspace = "/data/liyang/trunk/build64_debug/workspace";

my @src_filelist = glob "$src_workspace/*"; 
my @release_filelist = glob "$release_workspace/*"; 
my @debug_filelist = glob "$debug_workspace/*"; 


#print "filelist in $src_workspace\n";
#print map $_ . "\n", @src_filelist;
#print "\n";
#
#print "filelist in $release_workspace\n";
#print map $_ . "\n", @release_filelist;
#print "\n";
#
#print "filelist in $debug_workspace\n";
#print map $_ . "\n", @debug_filelist;
#print "\n";

open SHELL, ">clean_workspace.sh";
print SHELL '#!/bin/bash';
print SHELL "\n";
clean_workspace(\@release_filelist, \@src_filelist);
clean_workspace(\@debug_filelist, \@src_filelist);

close(SHELL);
