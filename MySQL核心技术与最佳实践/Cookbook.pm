package Cookbook;



use strict;
use warnings;
use DBI;



my $db_name = "cookbook";
my $host_name = "localhost";
my $user_name = "root";
my $password = "root";
my $port_num = undef;
my $socket_file = undef;

sub connect
{
	my $dsn = "DBI:mysql:host=$host_name";
	my %conn_attrs = (PrintError => 0, RaiseError => 1, AutoError => 1);
	$dsn .= ";database=$db_name" if defined $db_name;
	$dsn .= ";mysql_socket=$socket_file" if defined $socket_file;
	$dsn .= ";port=$port_num" if defined $port_num;
	return (DBI->connect ($dsn, $user_name, $password, \%conn_attrs));
}


1;  # return true;
