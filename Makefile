output: schedule_app.o
	g++ schedule_app.o -o schedule_app

schedule_app.o: schedule_app.cpp
	g++ -c schedule_app.cpp

clean: 
	rm *.o



