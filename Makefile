all: Register
Register: main.o Student.o Course.o Registration.o DataManager.o DataManagerHelper.o DataManagerFile.o DataManagerHTM.o
	g++ -std=c++11 -o Register main.o Student.o Course.o Registration.o DataManager.o DataManagerHelper.o DataManagerFile.o DataManagerHTM.o
main.o: main.cpp DataManager.h
	g++ -std=c++11 -c main.cpp
Student.o: Student.cpp Student.h SortedList.h
	g++ -std=c++11 -c Student.cpp
Course.o: Course.cpp Course.h SortedList.h
	g++ -std=c++11 -c Course.cpp
Registration.o: Registration.cpp Registration.h SortedList.h
	g++ -std=c++11 -c Registration.cpp
DataManager.o: DataManager.cpp
	g++ -std=c++11 -c DataManager.cpp
DataManagerHelper.o: DataManagerHelper.cpp
	g++ -std=c++11 -c DataManagerHelper.cpp
DataManagerFile.o: DataManagerFile.cpp
	g++ -std=c++11 -c DataManagerFile.cpp
DataManagerHTM.o: DataManagerHTM.cpp
	g++ -std=c++11 -c DataManagerHTM.cpp

clean:
	rm *.o
