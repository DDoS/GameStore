#!/usr/bin/perl -wT
use strict;
use CGI ':standard';

# Get all POST parameters
my $fullname = param('fullname');
my $username = param('username');
my $password = param('password');

# Check if username already exists
sub exist(){
        return 1;
}

# Render error page
sub displayError(){
        print "Username is taken. <a href='registration.html'>Try again</a> or go to <a href='index.html'>homepage</a>.\n";
}

# Display resulting HTML page
print "Content-type: text/html\n\n";
if (exist()){
        displayError();
}