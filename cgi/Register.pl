#!/usr/bin/perl -wT

use strict;
use CGI ':standard';

# Get all POST parameters
my $fullname = param('fullname');
my $username = param('username');
my $password = param('password');

# Check if username already exists
sub exist(){
	open(users, "<database/Members.csv");
	my @lines = <users>;
	close users;
	foreach my $line (@lines)
	{
		chomp($line);
		my @tmp = split(',', $line);
		if($tmp[1] eq $username)
		{
			return 1;
		}
	}	
	my $user_info = "$fullname,$username,$password\n";
	open(users, ">>database/Members.csv");
	print users $user_info;
	close users;
	return 0;
}

# Render error page
sub error(){
    print "Username is taken. <a href='registration.html'>Try again</a> or go to <a href='index.html'>homepage</a>.\n";
}

# Render success page
sub success(){
    print "Account succesfully created, <a href='login.html'>sign in</a> now!\n";
}

# Display resulting HTML page
print "Content-type: text/html\n\n";
if (exist()){
    error();
} else {
    success();
}
