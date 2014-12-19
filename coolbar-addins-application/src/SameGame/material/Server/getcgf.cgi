#! /usr/local/bin/perl

require '/XXXXXX/common/common.pl';
require '/XXXXXX/common/CGI_LIB.pl';

&Parse_Data();
$filename = $CGI{'fn'};

##
## Main
##
{
	open( hFile, "<./$filename" );
	$len = -s $filename;
	read( hFile, $data, $len );
	close( hFile );
	print "Content-Type: application/samegame\n";
	print "Content-length:$len\n\n";
	print $data;
	exit;
}

