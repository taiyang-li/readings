#!/usr/bin/perl
use strict;
use warnings;
use DBD::mysql;
use DBI;

my  $dsn = "DBI:mysql:host=localhost;database=cookbook";
my  $dbh = DBI->connect($dsn, "root", "root") or die "error";
print "connected\n";
$dbh->disconnect();
print "disconnected\n";
