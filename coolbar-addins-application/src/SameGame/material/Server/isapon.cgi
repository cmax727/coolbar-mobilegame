#!/usr/bin/perl

require	'../../common/common.pl';
require	'../../common/CGI_LIB.pl';

&Parse_Data();
$uid	= $CGI{'uid'};
$PID	= $CGI{'pid'};
# =============================================================
#
#
# =============================================================
{
	## connect to data base 
	ConnectOracle();
	
	## check user data
	$Q	 = "select active from user_log where userid = '$uid'";
	$sth = $dbh->prepare($Q) or die($DBI::errstr);
	$r	 = $sth->execute     or die($DBI::errstr);
	($active) = $sth->fetchrow_array;
	$sth->finish;

	$active = 1;

	if ($active == 0)
	{
		$MESS = "0\n0\n0\n";
		$mlength = length($MESS);

		print "Content-type:text/plain\n";
		print "Content-length:$mlength\n\n";
		print $MESS;
	}

	if ($PID eq "001")
	{
		($tmp, $score1) = getTable($uid, "H001L0", "USERID", "", "POINT");
		($tmp, $score2) = getTable($uid, "H001L1", "USERID", "", "POINT");
		($tmp, $score3) = getTable($uid, "H001L2", "USERID", "", "POINT");
	}elsif( $PID eq "003" ){
		$Q = "select point from H003n where userid = '$uid'";
		$sth = $dbh->prepare($Q) or die($DBI::errstr);
		$r   = $sth->execute     or die($DBI::errstr);
		($score1) = $sth->fetchrow_array;
		$sth->finish;
	
		$Q = "select point from H003s where userid = '$uid'";
		$sth = $dbh->prepare($Q) or die($DBI::errstr);
		$r   = $sth->execute     or die($DBI::errstr);
		($score2) = $sth->fetchrow_array;
		$sth->finish;
	
		$Q = "select point from H003t where userid = '$uid'";
		$sth = $dbh->prepare($Q) or die($DBI::errstr);
		$r   = $sth->execute     or die($DBI::errstr);
		($score3) = $sth->fetchrow_array;
		$sth->finish;
	}
	$dbh->disconnect;

	if( $score1 eq ''){
		$score1 = 0;
	}
	if( $score2 eq ''){
		$score2 = 0;
	}
	if( $score3 eq ''){
		$score3 = 0;
	}

	$MESS = "$score1\n$score2\n$score3\n";
	$mlength = length($MESS);

    print "Content-type:text/plain\n";
	print "Content-length:$mlength\n\n";
	print $MESS;

    exit;
}
