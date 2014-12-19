#!/usr/bin/perl

require	'../../common/common.pl';
require	'../../common/CGI_LIB.pl';

&Parse_Data();
$uid	= $CGI{'uid'};
$PID	= $CGI{'pid'};
$TABLE	= $CGI{'ta'};
$SCORE	= $CGI{'sc'};

# =============================================================
#
#
# =============================================================
{
	print STDERR "[score.cgi] $uid-$TABLE-$SCORE\n";

	## connect to data base 
	ConnectOracle();
	
	## check user data
	$Q	 = "select active from user_log where userid = '$uid'";
	$sth = $dbh->prepare($Q) or die($DBI::errstr);
	$r	 = $sth->execute     or die($DBI::errstr);
	($active) = $sth->fetchrow_array;
	$sth->finish;

	$active = 1;

	if ($active == 0){
		print "Content-type:text/plain\n";
		print "Content-length:3\n\n";
		print "NG\n";
		exit;
	}

	$Q = "select userid from $TABLE where userid = '$uid'";
	$sth = $dbh->prepare($Q) or die($DBI::errstr);
	$r   = $sth->execute     or die($DBI::errstr);
	($check_score) = $sth->fetchrow_array;
	$sth->finish;

	if ($check_score ne $uid){
		$Q = "insert into $TABLE values ('$uid', $SCORE, sysdate)";
		$sth = $dbh->prepare($Q) or die($DBI::errstr);
		$r   = $sth->execute     or die($DBI::errstr);
	}else{
		$Q = "update $TABLE set point = $SCORE , reg_date = sysdate where userid = '$uid'";
		$sth = $dbh->prepare($Q) or die($DBI::errstr);
		$r   = $sth->execute     or die($DBI::errstr);
	}
	$sth->finish;
	$dbh->commit;
	$dbh->disconnect;

    print "Content-type:text/plain\n";
	print "Content-length:3\n\n";
	print "OK\n";

    exit;
}
