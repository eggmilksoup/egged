egged: egged.c
	cc egged.c -o egged

install: egged
	cp egged /usr/local/bin/egged
