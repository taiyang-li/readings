#!/usr/bin/perl

use Config::Tiny;
use POSIX qw(strftime);
use File::Basename;

sub read_config;
# sub read_full_config;
# sub read_incremental_config;
sub show_usage;
sub set_lock;
sub log_info;
sub log_error;
sub clear_old_file;
sub rsync;
sub fetch_file;
sub get_savepoint;
sub set_savepoint;
sub get_filelist_to_rsync;
sub get_dst_filename;
sub check_src_done;

our $Config;
our $file_type;

our $src_path;
# our $src_filename;
our $src_file_prefix;
our $src_file_separator;
our $src_suffix;
our $dst_path;
our $dst_file_prefix;
our $dst_file_separator;
our $dst_file_suffix;
our $save_days;
our $how_to_name;

our $info_log_file;
our $error_log_file;
our $lock_file;
our $sp_file;
our @FMTS = ("%Y", "%m", "%d", "%H", "%M", "%S");

read_config;
set_lock;
clear_old_file;

our $LOG_DAY=strftime("%Y-%m-%d", localtime());
open INFO_LOG, ">>$info_log_file.$LOG_DAY";
open ERROR_LOG, ">>$error_log_file.$LOG_DAY";

log_error "hehe\n";
my $ret = fetch_file;
if ($ret != 0)
{
	exit -1;
}

log_info "Done.\n";
exit 0;

sub read_config
{
	if (@ARGV < 1)
	{
		show_usage;
		exit -1;
	}

	$Config = Config::Tiny->new;
	$Config = Config::Tiny->read($ARGV[0]);
	$file_type = $Config->{_}->{file_type};
	log_info "file_type: $file_type\n";

	# src 
	$src_path = $Config->{src}->{path};
	$src_file_prefix = $Config->{src}->{file_prefix};
	$src_file_separator = $Config->{src}->{file_separator};
	$src_file_suffix = $Config->{src}->{file_suffix};
	$src_use_done = $Config->{src}->{use_done};

	# dst
	$dst_path = $Config->{dst}->{path};
	$dst_file_prefix = $Config->{dst}->{file_prefix};
	$dst_file_separator = $Config->{dst}->{file_separator};
	$dst_file_suffix = $Config->{dst}->{file_suffix};
	$save_days = $Config->{dst}->{save_days};
	$how_to_name = $Config->{dst}->{how_to_name};
	$dst_use_done = $Config->{dst}->{use_done};

	# log
	$info_log_file = $Config->{log}->{info_log};
	$error_log_file = $Config->{log}->{error_log};

	# lock 
	$lock_file = $Config->{lock}->{file};

	# savepoint
	if ($file_type == "incremental")
	{
		$sp_file = $Config->{savepoint}->{file};
	}
}

sub show_usage
{
	print "Usage: perl fetch-file.pl <config-file>\n";
	print "Please try again.\n";
}

sub set_lock
{
	log_info "set lock on this process\n";
	if( -e "$lock_file")
	{
		open(LOCKFILE, "$lock_file");
		my $lock_pid = <LOCKFILE>;
		if($lock_pid ne "")
		{
			my $cfg_file = $ARGV[0];
			print "process : $0 $cfg_file\n";
			my $ret = `ps -ef | grep $0 | grep perl | grep $cfg_file |  grep -v grep | awk '{print \$2;}' | grep $lock_pid`;
			if( $ret ne "" )
			{
				log_error "process $0 $cfg_file is already running: $lock_pid";
				exit -3;
			}
		}
		close(LOCKFILE);
	}
	open(LOCKFILE, ">$lock_file");
	print LOCKFILE $$;
	close(LOCKFILE);
}

sub log_info
{
	my @msg = @_;
	my @t = localtime;
	my $currtime = strftime("%Y-%m-%d %H:%M:%S,000.000", localtime);
	print INFO_LOG "[$currtime][$$][INFO][MESSAGE]".(join "", @msg);
	print "[$currtime][$$][INFO][MESSAGE]".(join "", @msg);
}

sub log_error
{
	my @msg = @_;
	my @t = localtime;
	my $currtime = strftime("%Y-%m-%d %H:%M:%S,000.000", localtime);
	print ERROR_LOG "[$currtime][$$][ERROR][MESSAGE]".(join "", @msg);
	print "[$currtime][$$][ERROR][MESSAGE]".(join "", @msg);
}

sub clear_old_file
{
	log_info "clear old file $save_days days ago\n";
	my $file = "$dst_path/$dst_file_prefix" . "$dst_file_separator" . "*";
	system("find $file -ctime +$save_days -print -exec rm \\{\\} \\;");
}

sub rsync
{
	# 增加重试功能
	my $src = shift;
	my $dst = shift;
	my $tmp = dirname($dst) . "/.tmp." . basename($dst);
	my $ret = system("rsync $src $tmp");
	while ($ret != 0)
	{
		log_error "rsycn $src $tmp faild, ret: $ret, try again\n";
		system("rm -rf $tmp");
		$ret = system("rsync $src $tmp");
		sleep(1);
	}
	$ret = system("mv $tmp $dst");
	return $ret;

}

sub fetch_file 
{
	log_info "start to fetch file\n";
	my @filelist = get_filelist_to_rsync;
	for my $file (@filelist)
	{
		my $src = $src_path . "/" . $file;	
		my $tmp = get_dst_filename $file;
		my $dst = "$dst_path/$tmp"; 
		log_info "start rsync $src $dst\n";
		my $ret = rsync $src, $dst; 
		log_info "finish rsync $src $dst\n";

		# touch savepoint
		if ($ret == 0 && $file_type eq "incremental")
		{
			set_savepoint $file;
		}

		# touch done file
		if ($ret == 0 && $dst_use_done eq "yes")
		{
			my $touch_ret = 0;
			do
			{
				log_info "touch done file: $dst_path/done.$tmp\n";
				$touch_ret = system("touch $dst_path/done.$tmp");
			} while ($touch_ret != 0);
		}
		sleep 1;
	}
	return 0;
}

sub get_savepoint
{
	log_info "get savepoint\n";

	open FD, "$sp_file" or return "";
	my $sp= <FD>;
	close FD;
	if ($sp eq "")
	{
		log_error "savepoint file $sp_file is empty\n";
	}
	return $sp;
}

sub set_savepoint
{
	my $sp = shift;
	log_info "set savepoint $sp\n";
	open FD, ">$sp_file";
	print FD $sp;
	close FD;
}

sub get_filelist_to_rsync
{
	log_info "get filelist to rsync\n";
	my @filelist;

	if ($file_type eq "full")
	{
		$file = $src_file_prefix . $src_file_separator . $src_file_suffix;
		my $ret = 0;
		$ret = check_src_done $file if ($src_use_done eq "yes");
		if ($ret == 0)
		{
			log_info "add file to filelist: $file\n";
			push @filelist, $file;
		}
	}
	elsif ($file_type eq "incremental")
	{
		my $tmp = "$src_path/$src_file_prefix$src_file_separator" . "*";
		my @allfiles = `rsync $tmp`;
		my $sp = get_savepoint;
		foreach my $file (@allfiles)
		{
			# print $file . "\n";
			if ($file =~ m/$src_file_prefix$src_file_separator(.*)$/)
			{
				$file = "$src_file_prefix$src_file_separator$1";
				if ($file gt $sp)
				{
					my $ret = 0;
					$ret = check_src_done $file if ($src_use_done eq "yes");
					if ($ret == 0)
					{
						log_info "add file to filelist: $file\n";
						push @filelist, $file;
					}
					else
					{
						last;
					}
				}
			}
		}
	}
	return @filelist;
}

sub get_dst_filename
{
	my $in_name = shift;
	my $out_name; 

	if ($how_to_name eq "from_current_time")
	{   
		$out_name = "${dst_file_prefix}${dst_file_separator}" . strftime($dst_file_suffix, localtime());
	}   
	elsif ($how_to_name eq "from_source_file")
	{   
		my %fmt_val_hash;
		my @fmts = ($src_file_suffix =~ m/(%[YmdHMS])/g);
		$in_name =~ s/^$src_file_prefix${src_file_separator}20//;
		my @vals = ($in_name =~ m/(\d\d)/g);
		$vals[0] = "20" . $vals[0];

		if (scalar(@fmts) != scalar(@vals))
		{   
			print "src_file_suffix doesn't match the format of source files\n"; 
			exit -4; 
		}   
		for (my $i=0; $i<scalar(@fmts); $i++)
		{   
			$fmt_val_hash{@fmts[$i]} = $vals[$i];
		}   

		$out_name = $dst_file_suffix;
		foreach my $fmt (@FMTS)
		{
			if (! defined($fmt_val_hash{$fmt}))
			{
				$fmt_val_hash{$fmt} = "00";
			}
			$out_name =~ s/$fmt/$fmt_val_hash{$fmt}/g
		}
		$out_name = $dst_file_prefix . $dst_file_separator . $out_name;
	}
	return $out_name;
}

sub check_src_done
{
	log_info "check done file\n";

	my $filename = shift;
	if ($filename eq "")
	{
		log_error "input param of check_src_done is empty\n";
		return -1;
	}
	my $done_filename = "done." . $filename;	
	my $ret = `rsync $src_path/$done_filename`;
	if ($ret eq "")
	{
		log_error "done file $done_filename doesn't exists\n";
		return -2;
	}
	return 0;
}
