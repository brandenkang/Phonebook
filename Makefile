
output: project3header.o project3.o 
	g++ project3header.o project3.o -o fonbook
project3header.o: project3header.cpp project3header.h
	g++ -c project3header.cpp
project3.o: project3.cpp 
	g++ -c project3.cpp
clean:
	rm *.o fonbook
