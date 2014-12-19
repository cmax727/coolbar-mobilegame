#!/usr/bin/perl

require '/XXXXXX/common/CGI_LIB.pl';

@easy = (
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000"
	);
@normal = (
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000"
	);
@difficalt = (
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000",
	"000 146 000"
	);

$game_level = 0;
$chip_type = 0;
&Parse_Data();
$game_level = $CGI{'gl'};
$chip_type = $CGI{'ct'};

##
## Main
##
{
	$color = '';
	if( $game_level eq '0' ){
		$color = $easy[$chip_type];
	}elsif( $game_level eq '1' ){
		$color = $normal[$chip_type];
	}elsif( $game_level eq '2' ){
		$color = $difficalt[$chip_type];
	}
	$len = length( $color );
	print "Content-type:text/plain\n";
	print "Content-length:$len\n\n";
	print $color;
	exit;
}

