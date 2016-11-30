all: Register
Register: main.o Student.o Course.o Registration.o DataManager.o
	g++ -std=c++11 -o Register main.o Student.o Course.o Registration.o DataManager.o
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
Student.o: Student.cpp Student.h SortedList.h
	g++ -std=c++11 -c Student.cpp
Course.o: Course.cpp Course.h SortedList.h
	g++ -std=c++11 -c Course.cpp
Registration.o: Registration.cpp Registration.h SortedList.h
	g++ -std=c++11 -c Registration.cpp
DataManager.o: DataManager.cpp
	g++ -std=c++11 -c DataManager.cpp
clean:
	rm *.o
