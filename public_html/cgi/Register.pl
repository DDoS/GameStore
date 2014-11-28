#!/usr/bin/perl -wT
use strict;
use CGI ':standard';

# Get all POST parameters
my $fullname = param('fullname');
my $username = param('username');
my $password = param('password');

# Check if username already exists
sub exist(){
    return 0;
}

# Render error page
sub error(){
    print "Username is taken. <a href='../registration.html'>Try again</a> or go to <a href='../index.html'>homepage</a>.\n";
}

# Render success page
sub success(){
    print "Account succesfully created, <a href='../login.html'>sign in</a> now!\n";
}

# Display resulting HTML page
print "Content-type: text/html\n\n";
if (exist()){
    error();
} else {
    success();
}