#!/usr/bin/env python
import os
import sys
import cgi, cgitb

cgitb.enable()
form = cgi.FieldStorage()

def checkLogged(username):
	try:
		loggedin = open("database/LoggedIn.csv", 'r')
		users = loggedin.read();
		users = users.split(',')
		for usr in users:
			if username == usr:
				loggedin.close()
				return True
	except IOError, (errno, strerror):
		print "I/O error(%s): %s" % (errno, strerror)
	loggedin.close()
	return False

def notLogged():
	print "Content-Type: text/html"
	print
	print """
		<html>
		<head><title>Not logged in</title><head>
		<body>
		You are not logged in, please do not try to scam the system
		<br>
		<a href='/catalogue.html'>Get back to the catalogue</a>
		</body>
		</html>

"""	

if form.has_key("username"):
	user = form["username"]
	if checkLogged(user):
		a=1+1
	else:
		notLogged()
else:
	print "error"
