#!/usr/bin/perl -w
$Test_String = <STDIN> ;
$Regex_Pattern = '(b)?o\1';
$Test_String =~ /$Regex_Pattern/g ? print 'true' : print 'false';
