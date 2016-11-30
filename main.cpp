//
//  main.cpp
//  Project5
//
//  Created by Kyle Lei on 24/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include <iostream>
#include <cstdlib>
//#include "SortedList.h"
#include "Student.h"
#include "Course.h"
#include "Registration.h"
#include "DataManager.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
//    StudentTable table;
//    Student sb("20123928","SB",3,Student::Gender::Male);
//    Student so("20123928","SO",3,Student::Gender::Male);
//    Student co("20327909","QT",3,Student::Gender::Female);
//    table.addStudent(so);
//    table.addStudent(sb);
//    table.addStudent(co);
//    cout<<table.findStudent("20123928")->getName()<<endl;
//    CourseTable ctable;
//    Course fuckthis("COMP2012H", "Honors OOP&DS", 5);
//    Course fuckthat("ELEC2400", "Electronic Circuits", 4);
//    ctable.addCourse(fuckthis);
//    ctable.addCourse(fuckthat);
//    cout<<ctable.findCourse("ELEC2400")->getName()<<endl;
    DataManager dat;
    dat.displayStudentMenu();
    dat.insertStudent();
    dat.queryStudent();
    dat.deleteStudent();
    return dat.exec();
}
