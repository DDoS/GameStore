a.out:
	gcc -o cgi/a.cgi cgi/Login.c

clean:
	rm -f cgi/a.cgi

publish:
	rm -rf ~/public_html/*
	cp -rf html/* ~/public_html
	cp -rf cgi/* ~/public_html
	cp -rf database ~/public_html
	# make all files rwxr-xr-x, a bit too permissive but simple
	chmod -R 755 ~/public_html

