——————————————
General Design
——————————————
The registration database keeps record of students and courses information, as well as course enrollment information. It is also capable of outputting information stored in the form of HTML document and saving the entire database to a file.

The overall design of the program is highly object-oriented with an extremely simple main and other objects finishing the tasks. No global variable or function is present, except for a simple macro definition in “DataManagerFile.cpp”, which can be removed if needs be.

Class inheritance is not adopted since the input datatypes vary significantly.

——————————————
Classes Design
——————————————
****** SortedList ******
First, as required, a doubly sorted linked list class “SortedList” with template is created for collision handling when hashing.

****** Student & Course ******
Two classes “Student” and “Course” are defined as basic entries into the database, each keeping its own information, such as its name, ID for a student and code for a course. At the same time, classes “StudentTable” and “CourseTable” act as hash tables with easy-to-use interfaces.

****** Registration ******
The course enrollment record itself stores the pointer to the corresponding student and course, instead of the actual entry of student and course in case any of them changed. The corresponding student and course also each stores the pointer to the enrollment record to facilitate outputs. There is also a “RegistraionTable” class to manipulate the underlying sorted list of registrations.

****** DataManager ******
The “DataManager” class is the most important class. The class keeps objects of tables needed for the database, takes in input from standard input and files, verifies them simultaneously, and outputs to standard output and files. The implementation of this class is so lengthy that it has to be put into 4 separate source files. First it is the manipulation of records. Then the helper functions that helps to verify inputs, and manipulate file outputs, such as separating different records with char(29), different entries char(30) and different contents char(31). Next the file I/O that reads and writes file. Finally the HTML output that reads the tables and format the HTML file.

The most tricky part is the registration management. That is, the addition and deletion of course enrollment, as well as the deletion of student and course. Due to my data structure, when adding a registration record, it has to be linked to the corresponding student and course, and the student and course also need to link to the record. The deletion of a registration record also requires that not only the record itself needs to be deleted, the link in the corresponding student and course to this record also need to be deleted. Moreover, the deletion of course and student also requires the deletion of registration records of students taking the course and course taken by the student.

——————
Notice
——————
* A sample database “dat” has been provided for grader to load
* The sample executable outputs an HTML file with two “<HEAD>”, which is fixed in my program
* The university has updated its programs to 4 year, even 5 year for DDP, and course code to 4-digit. Therefore in my program the year limit has been set to 4 and course code 4-digit