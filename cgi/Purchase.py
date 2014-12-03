#!/usr/bin/env python
import os
import sys
import cgi, cgitb

cgitb.enable()
form = cgi.FieldStorage()
def checkLogged(username):
	try:
		loggedin = open("../database/LoggedIn.csv", 'r')
		users = loggedin.read()
		loggedin.close()
		users = users.rstrip()
		users = users.split(',')
		for usr in users:
		#	print "%s + %s" % (username, usr)		
			if username == usr:
				return True
	except IOError, (errno, strerror):
		print "I/O error(%s): %s" % (errno, strerror)
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
		<a href='../catalogue.html'>Get back to the catalogue</a>
		</body>
		</html>
		"""	

def purchase():
	print "Content-Type: text/html"
	print
	print """<html>
		<head>	<title>	Purchase page </title> </head>
		<body>
		"""
	invent = []
	item_name = [0]*6
	item_price = [0]*6
	item_quantity = [0]*6
	buying = [0]*6
	inventory_file = open("../database/Inventory.csv", 'r')
	invent = inventory_file.readlines()
	for i in range(0, len(invent)):
		item_name[i] = invent[i].split(',')[0]
		item_price[i] = int(invent[i].split(',')[1])
		item_quantity[i] = int(invent[i].split(',')[2])
	inventory_file.close()
	if form.has_key("buy_chest1") == True:
		buying[0] = int(form["quantity_chest1"].value)
	if form.has_key("buy_hat1") == True:
		buying[1] = int(form["quantity_hat1"].value)
	if form.has_key("buy_head1") == True:
		buying[2] = int(form["quantity_head1"].value)
	if form.has_key("buy_pants3") == True:
		buying[3] = int(form["quantity_pants3"].value)
	if form.has_key("buy_pin") == True:
		buying[4] = int(form["quantity_pin"].value)
	if form.has_key("buy_powerup3") == True:
		buying[5] = int(form["quantity_powerup"].value)
	total = 0
	for i in range (0, 6):
		if buying[i] == 0:
			continue
		if buying[i] > item_quantity[i]:
			buying[i] = item_quantity[i]
		total += buying[i]*item_price[i]
		print "Item: " + item_name[i] + " Quantity: " + str(buying[i]) + " Price: " + str(buying[i]*item_price[i]) + "<br>"
	print "Total: " + str(total) + "<br>"
	print "<a href='../catalogue.html'>Get back to the catalogue</a> <br>"
	print "<a href='../index.html'>Home Page</a> <br>"
	print """
		</body>
		</html>
		"""	
	inventory_file = open("../database/Inventory.csv", 'w')
	for i in range (0, 6):
		inventory_file.write(item_name[i]+','+str(item_quantity[i]-buying[i])+','+str(item_price[i]))
	inventory_file.close()
if form.has_key("username"):
	user = form["username"].value
	if checkLogged(user):
		purchase()	
	else:
		notLogged()
else:
	print "Content-Type: text/plain"
	print
	print "Error: username variable not found"
