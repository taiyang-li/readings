#!/usr/bin/perl

use strict;
use warnings;
use Cookbook;



my $dbh;
eval
{
	$dbh = Cookbook::connect();
	print "connected\n";
};

die "$@" if $@;
$dbh->disconnect();
print "disconnected\n";
