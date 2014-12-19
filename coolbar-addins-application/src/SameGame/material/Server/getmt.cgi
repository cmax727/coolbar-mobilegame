#!/usr/bin/perl

require '/XXXXXX/common/CGI_LIB.pl';
require '/XXXXXX/common/common.pl';

##
## Main
##
{
	$mt = JudgeMachineType();
	$len = length( $mt );
	print "Content-type:text/plain\n";
	print "Content-length:$len\n\n";
	print $mt;
	exit;
}

