#!/usr/bin/perl

require '/XXXXXX/common/CGI_LIB.pl';

$index	= 0;
@file	= 0;
&Parse_Data();
$filename = $CGI{'fn'};

##
## Main
##
{

	open( hFile, "<./$filename" );
	while( <hFile> ){
		push @file, $_;
		$index++;
	}
	close(hFile);

	$index	= 1; $len = 0;
	while ($file[$index] ne ''){
		$file[$index] =~ s/\r//g;
		$file[$index] =~ s/\n//g;
		$len += length($file[$index]);
		$len += 1;		## 改行コードの分
		$index++;
	}

	print "Content-type:text/plain\n";
	print "Content-length:$len\n\n";
	$index	= 1;
	while ($file[$index] ne '')
	{
		print $file[$index] . "\n";
		$index++;
	}
	exit;
}

