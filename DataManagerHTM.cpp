//
//  DataManagerHTM.cpp
//  Project5
//
//  Created by Kyle Lei on 2/12/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

void DataManager::displayHTMMenu(){
    system("clear");
    cout<<"HKUST Course Registration System  (Report Generation Menu)\n"
    <<"----------------------------------------------------------\n"<<endl
    <<"1. List all student information\n"
    <<"2. List all course information\n"
    <<"3. List all courses of a student\n"
    <<"4. List all students of a course\n"
    <<"5. Go back to main menu\n"<<endl
    <<"Enter your choice (1-5): ";
    
    int choice;
    readInput(choice);
    while(!verifyChoice(choice, 5)){
        cout<<"Invalid input, re-enter (1-5): ";
        readInput(choice);
    }
    switch (choice) {
        case 1:
            htmAllStudents();
            break;
            
        case 2:
            htmAllCourses();
            break;
            
        case 3:
            htmCourseOfStudent();
            break;
            
        case 4:
            htmStudentOfCourse();
            break;
            
        case 5:
            break;
    }
}

void DataManager::htmAllStudents(){
    ofstream fout("Students.html");
    if(!fout.is_open()){
        cout<<"Error: Write File Error\n"<<endl;
        waitForEnter();
        return;
    }
    
    const int size=stuTable.getSize();
    if(size!=0){
        addHTMLStart(fout, "All Students List",true);
        //add table title
        fout<<"<TR>\n"
        <<"<TD>Student ID</TD>\n"
        <<"<TD>Student Name</TD>\n"
        <<"<TD>Year</TD>\n"
        <<"<TD>Gender</TD>\n"
        <<"</TR>\n\n";
        
        //sort students
        Student* students=new Student[size];
        int top=0;
        for(int i=0;i<stuTable.getBucketNum();++i){
            for(int j=0;j<stuTable.getTable()[i].getSize();++j){
                students[top]=stuTable.getTable()[i][j];
                ++top;
            }
        }
        sort(students, students+size);
        
        for(int i=0;i<size;++i){
            Student* stuptr=students+i;
            fout<<"<TR>\n";
            fout<<"<TD>"<<stuptr->getID()<<"</TD>\n"
            <<"<TD>"<<stuptr->getName()<<"</TD>\n"
            <<"<TD>"<<stuptr->getYear()<<"</TD>\n"
            <<"<TD>"<<strGender(stuptr->getGender())<<"</TD>\n</TR>\n\n";
        }
        addHTMLEnd(fout,true);
        delete []students;
    }
    else{
        addHTMLStart(fout, "All Students List",false);
        fout<<"No student found\n";
        addHTMLEnd(fout, false);
    }
    
    fout.close();
    cout<<"Output successful\n"<<endl;
    waitForEnter();
}

void DataManager::htmAllCourses(){
    ofstream fout("Courses.html");
    if(!fout.is_open()){
        cout<<"Error: Write File Error\n"<<endl;
        waitForEnter();
        return;
    }
    
    const int size=courseTable.getSize();
    if(size!=0){
        addHTMLStart(fout, "All Course List",true);
        //add table title
        fout<<"<TR>\n"
        <<"<TD>Course Code</TD>\n"
        <<"<TD>Course Name</TD>\n"
        <<"<TD>Credit</TD>\n"
        <<"</TR>\n\n";
        
        //add courses' info
        Course* courses=new Course[size];
        int top=0;
        for(int i=0;i<courseTable.getBucketNum();++i){
            for(int j=0;j<courseTable.getTable()[i].getSize();++j){
                courses[top]=courseTable.getTable()[i][j];
                ++top;
            }
        }
        sort(courses,courses+size);
        
        for(int i=0;i<size;++i){
            Course* ptr=courses+i;
            fout<<"<TR>\n";
            fout<<"<TD>"<<ptr->getCode()<<"</TD>\n"
            <<"<TD>"<<ptr->getName()<<"</TD>\n"
            <<"<TD>"<<ptr->getCredit()<<"</TD>\n\n";
        }
        addHTMLEnd(fout,true);
        delete []courses;
    }
    else{
        addHTMLStart(fout, "All Course List",false);
        fout<<"No course found\n";
        addHTMLEnd(fout, false);
    }
    
    fout.close();
    cout<<"Output successful\n"<<endl;
    waitForEnter();
}

void DataManager::htmCourseOfStudent(){
    cout<<"Enter the student ID: ";
    string in_ID;
    readInput(in_ID);
    while(!verifyStuID(in_ID)){
        cout<<"Invalid Input, please re-enter [student ID]: ";
        readInput(in_ID);
    }
    Student* stuptr=stuTable.findStudent(in_ID);
    if(stuptr==NULL){
        cout<<"Student does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    string filename;filename+=in_ID;filename+=".html";
    ofstream fout(filename);
    if(!fout.is_open()){
        cout<<"Error: Write File Error\n"<<endl;
        waitForEnter();
        return;
    }
    
    string title;
    title+="Course Records for Student: ";title+=stuptr->getName();
    title+=" (";title+=stuptr->getID();title+=")";
    SortedList<Registration*>* reg=stuptr->getEnrolledCourses();
    int size=reg->getSize();
    if(size!=0){
        addHTMLStart(fout, title,true);
        //add table title
        fout<<"<TR>\n"
        <<"<TD>Course Code</TD>\n"
        <<"<TD>Course Name</TD>\n"
        <<"<TD>Credit</TD>\n"
        <<"<TD>Exam Mark</TD>\n"
        <<"</TR>\n\n";
        Registration* regs=new Registration[size];
        int top=0;
        for(int i=0;i<reg->getSize();++i){
            regs[top]=*reg->operator[](i);
            ++top;
        }
        sort(regs,regs+size);
        
        for(int i=0;i<size;++i){
            Registration* regToAdd=regs+i;
            fout<<"<TR>\n";
            fout<<"<TD>"<<regToAdd->getCourse()->getCode()<<"</TD>\n"
            <<"<TD>"<<regToAdd->getCourse()->getName()<<"</TD>\n"
            <<"<TD>"<<regToAdd->getCourse()->getCredit()<<"</TD>\n";
            if(regToAdd->isGradeAvailable()) fout<<"<TD>"<<regToAdd->getMark()<<"</TD>\n</TR>\n\n";
            else fout<<"<TD>N/A</TD>\n\n";
        }
        addHTMLEnd(fout, true);
        delete []regs;
    }
    else{
        addHTMLStart(fout, title, false);
        fout<<"No course taken\n";
        addHTMLEnd(fout, false);
    }
    
    fout.close();
    cout<<"Output successful\n"<<endl;
    waitForEnter();
}

void DataManager::htmStudentOfCourse(){
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    Course* ptr=courseTable.findCourse(in_code);
    if(ptr==NULL){
        cout<<"Course does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    string filename;filename+=in_code;filename+=".html";
    ofstream fout(filename);
    if(!fout.is_open()){
        cout<<"Error: Write File Error\n"<<endl;
        waitForEnter();
        return;
    }
    
    string title;
    title+="Student Records for Course: ";title+=ptr->getName();
    title+=" (";title+=ptr->getCode();title+=")";
    SortedList<Registration*>* reg=ptr->getEnrolledStudents();
    int size=reg->getSize();
    
    if(size!=0){
        addHTMLStart(fout, title,true);
        //add table title
        fout<<"<TR>\n"
        <<"<TD>Student ID</TD>\n"
        <<"<TD>Student Name</TD>\n"
        <<"<TD>Year</TD>\n"
        <<"<TD>Gender</TD>\n"
        <<"<TD>Exam Mark</TD>\n"
        <<"</TR>\n\n";
        Registration* regs=new Registration[size];
        int top=0;
        for(int i=0;i<reg->getSize();++i){
            regs[top]=*reg->operator[](i);
            ++top;
        }
        sort(regs,regs+size);
        
        for(int i=0;i<size;++i){
            Registration* regToAdd=regs+i;
            fout<<"<TR>\n";
            fout<<"<TD>"<<regToAdd->getStudent()->getID()<<"</TD>\n"
            <<"<TD>"<<regToAdd->getStudent()->getName()<<"</TD>\n"
            <<"<TD>"<<regToAdd->getStudent()->getYear()<<"</TD>\n"
            <<"<TD>"<<strGender(regToAdd->getStudent()->getGender())<<"</TD>\n";
            if(regToAdd->isGradeAvailable())
                fout<<"<TD>"<<regToAdd->getMark()<<"</TD>\n</TR>\n\n";
            else fout<<"<TD>N/A</TD>\n</TR>\n\n";
        }
        addHTMLEnd(fout, true);
        delete []regs;
    }
    else{
        addHTMLStart(fout, title, false);
        fout<<"No student takes this course\n";
        addHTMLEnd(fout, false);
    }
    
    fout.close();
    cout<<"Output successful\n"<<endl;
    waitForEnter();
}
