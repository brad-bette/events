events: events-cal.cpp
	g++ -o events events-cal.cpp

install:
	mv events /usr/local/bin/ && cp events.txt ~/

remove:
	rm /usr/local/bin/events && rm ~/events.txt
