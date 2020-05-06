#!/usr/bin/perl -w 

use POSIX qw(strftime);

$TABLE_NAME = "sogoukey";
$TABLE_ID = 10;
$MYSQLTOOL_HOME = "/opt/app/mysqltool/bin";
$CHECK_SOGOUKEY_DATA_HOME = "/data/check_sogoukey";
$CHECK_SOGOUKEY_LOG_HOME = "/opt/logs/check_sogoukey";
$CENTRE_IP = "octopus.base.biz";
$CENTRE_PORT = 20130;
$DB_NAME = "adonline_mysql_read";
#$DB_NAME = "sadonline_for_dev";
$IELOG_PATH = "/data/feed-xuri/bid/add";
$IELOG_INTERVAL = 5;
$IELOG_PREFIX = "ie_log_";
$MODE = "hourly";

# init mode 
my $param_no = @ARGV;
if ($param_no >= 1)
{
	if ($ARGV[0] eq "hourly" || $ARGV[0] eq "daily")
	{
		$MODE = $ARGV[0];
	}
}

$CUR_TIME = time();
if ($MODE eq "hourly")
{
	# back to last hour
	$PRE_TIME = $CUR_TIME - 3600;
	$CHECKED_TIME = strftime("%Y-%m-%d %H", localtime($PRE_TIME));
}
else
{
	#back to last day 
	$PRE_TIME = $CUR_TIME - 3600*24;
	$CHECKED_TIME = strftime("%Y-%m-%d", localtime($PRE_TIME)); 
}

# for test 
#$MODE = "hourly";
#$CHECKED_TIME = "2015-07-16 14";

$FILE_SUFFIX = join("-", split(" ", $CHECKED_TIME));
open LOG, ">> $CHECK_SOGOUKEY_LOG_HOME/check_sogoukey.log.$FILE_SUFFIX" || die("init info logger failed");
open LOG_ERROR, ">> $CHECK_SOGOUKEY_LOG_HOME/check_sogoukey.error.$FILE_SUFFIX" || die("init error logger failed");

print "start check $TABLE_NAME\n";
log_info("start check $TABLE_NAME");

print "dump tracer\n";
log_info("dump tracer");
my $ret = dump_tracer($MODE, $CHECKED_TIME);
if ($ret != 0)
{
	print "dump tracer failed\n";
	log_error("dump tracer failed");
	exit -1;
}

print "check sogoukey\n";
log_info("check sogoukey");
$ret = check_sogoukey($MODE, $CHECKED_TIME);
if ($ret != 0)
{
	print "check sogoukey wrong\n";
	log_info("check sogoukey wrong");
	exit -1;
}
print "check sogoukey right\n";
log_info("check sogoukey right");


################## functions ########################
sub log_info
{
	my @msg = @_;
	my @t = localtime();
	my $currtime = strftime("%Y-%m-%d %H:%M:%S,000.000", localtime);
	print LOG "[$currtime][$$][INFO][MESSAGE]".(join "", @msg)."\n";
}

sub log_error
{	
	my @msg = @_;
	my @t = localtime;
	my $currtime = strftime("%Y-%m-%d %H:%M:%S,000.000", localtime);
	print LOG_ERROR "[$currtime][$$][ERROR][MESSAGE]".(join "", @msg)."\n";
}

sub dump_tracer 
{	
	my $mode = shift;
	my $time = shift;
	my $sql = "select * from ad_tracer where tbl = $TABLE_ID and ts like '$time%' order by seq";
	my $suffix = $time;
	if ($mode eq "hourly")
	{
		$suffix = join("-", split(" ", $time));
	}

	my $cmd = "$MYSQLTOOL_HOME/MysqlTool -c $CENTRE_IP:$CENTRE_PORT -x -d \"\\t\" -p $CHECK_SOGOUKEY_DATA_HOME/ad_tracer.$suffix \"$DB_NAME\" \"$sql\"";
	my $ret = system($cmd);
	print "execute cmd: $cmd\n";
	log_info("execute cmd: $cmd");
	if ($ret != 0)
	{
		log_error("command $cmd execute failed");
		print "commmand $cmd execute failed\n";
		return -1;
	}
	return 0;
}

sub read_tracer_file
{
	my $file = shift;
	open(FILE,"<$file") || die("open file $file failed");
	my @seq_list;
	my @ts_list;
	while (<FILE>)
	{
		chomp;
		my @tmp = split("\t", $_);
		if ($#tmp + 1 != 4)
		{
			next;
		}
		push(@seq_list, $tmp[0]);
		push(@ts_list, $tmp[3]);
	}
	close(FILE);
	return (\@seq_list, \@ts_list);
}

sub check_sogoukey
{	
	my $mode = shift;
	my $time = shift;
	my %ielog_sogoukey_map;
	my $suffix = $time;
	if ($mode eq "hourly")
	{	
		$suffix = join("-", split(" ", $time));
	}

	my ($ref_seq_list, $ref_ts_list) = read_tracer_file("$CHECK_SOGOUKEY_DATA_HOME/ad_tracer.$suffix");
	my @seq_list = @$ref_seq_list;
	my @ts_list = @$ref_ts_list;
	my $seq_no = @seq_list;
	my $ts_no = @ts_list;

	# this is impossible
	if ($seq_no != $ts_no)
	{
		print "seq number is not equal to ts number, seq_no: $seq_no, ts_no: $ts_no\n";
		log_error("seq number is not equal to ts number, seq_no: $seq_no, ts_no: $ts_no\n");
		return -1;
	}	

	if ($seq_no == 0)
	{
		print "no seq for $TABLE_NAME\n";
		log_info("no seq $TABLE_NAME");
		return 0;
	}
	
	for (my $i=0; $i < $seq_no; $i++)
	{
		my $seq = $seq_list[$i];
		my $ts = $ts_list[$i];
		my $file = get_ielog_from_ts($ts); 
		if (exists($ielog_sogoukey_map{$file}))
		{
			$ielog_sogoukey_map{$file}++;
		}
		else
		{
			$ielog_sogoukey_map{$file} = 1;
		}
	}
	
	my @files = keys(%ielog_sogoukey_map);
	foreach $file (@files)
	{
		my $count = 0;
		open(FILE, "<$file") || die("open file i$file failed");
		while(<FILE>)
		{
			chomp;
			my $line = $_;
			if ($line =~ m/\bCL\b/)
			{
				$count++;
			}
		}

		print "check sogoukey in file $file, mode: $mode, time: $time, tracer count: $ielog_sogoukey_map{$file}, file count: $count\n";
		log_info("check sogoukey in file $file, tracer count: $ielog_sogoukey_map{$file}, file count: $count");
		if ($count != $ielog_sogoukey_map{$file})
		{
			print "check sogoukey in file $file, tracer count: $ielog_sogoukey_map{$file}, file count: $count\n";
			log_info("check sogoukey in file $file, tracer count: $ielog_sogoukey_map{$file}, file count: $count");
			return -1;
		}
	}
	my $cmd = "touch $CHECK_SOGOUKEY_DATA_HOME/sogoukey.success." . $suffix;
	$ret = system("$cmd");
	print "touch success file\n";
	log_info("touch success file");
	if ($ret != 0)
	{
		print "execute command $cmd failed\n";
		log_error("execute command $cmd failed");
		return -1;
	}
	return 0;
}

sub get_ielog_from_ts
{
	my $ts = shift;
	my @tmp = split(" ", $ts);
	my $prefix = $IELOG_PREFIX . join("", split("-", $tmp[0]));
	my $suffix;

	my @hour_min_sec = split(":", $tmp[1]);
	my $hour = $hour_min_sec[0];
	my $min = $hour_min_sec[1];
	$min = $min - $min % $IELOG_INTERVAL;
	$suffix = "$hour$min";

	return $IELOG_PATH . "/" . $prefix . "." . $suffix;
}


