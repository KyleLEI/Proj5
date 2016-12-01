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
            deleteStudent();
            break;
            
        case 4:
            queryStudent();
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
    
    if(!stuTable.isEmpty()){
        addHTMLStart(fout, "All Students List",true);
        //add table title
        fout<<"<TR>\n"
        <<"<TD>Student ID</TD>\n"
        <<"<TD>Student Name</TD>\n"
        <<"<TD>Year</TD>\n"
        <<"<TD>Gender</TD>\n"
        <<"</TR>\n\n";
        
        //add students' info
        for(int i=0;i<stuTable.getBucketNum();++i){
            for(int j=0;j<stuTable.getTable()[i].getSize();++j){
                fout<<"<TR>\n";
                Student* stuptr=&stuTable.getTable()[i][j];
                fout<<"<TD>"<<stuptr->getID()<<"</TD>\n"
                <<"<TD>"<<stuptr->getName()<<"</TD>\n"
                <<"<TD>"<<stuptr->getYear()<<"</TD>\n"
                <<"<TD>"<<strGender(stuptr->getGender())<<"</TD>\n\n";
            }
        }
        addHTMLEnd(fout,true);
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
    
    if(!courseTable.isEmpty()){
        addHTMLStart(fout, "All Course List",true);
        //add table title
        fout<<"<TR>\n"
        <<"<TD>Course Code</TD>\n"
        <<"<TD>Course Name</TD>\n"
        <<"<TD>Credit</TD>\n"
        <<"</TR>\n\n";
        
        //add courses' info
        for(int i=0;i<courseTable.getBucketNum();++i){
            for(int j=0;j<courseTable.getTable()[i].getSize();++j){
                fout<<"<TR>\n";
                Course* ptr=&courseTable.getTable()[i][j];
                fout<<"<TD>"<<ptr->getCode()<<"</TD>\n"
                <<"<TD>"<<ptr->getName()<<"</TD>\n"
                <<"<TD>"<<ptr->getCredit()<<"</TD>\n\n";
            }
        }
        addHTMLEnd(fout,true);
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
    ofstream fout("Courses.html");
    if(!fout.is_open()){
        cout<<"Error: Write File Error\n"<<endl;
        waitForEnter();
        return;
    }
    
    addHTMLStart(fout, "All Course List",true);
    //add table title
    fout<<"<TR>\n"
    <<"<TD>Course Code</TD>\n"
    <<"<TD>Course Name</TD>\n"
    <<"<TD>Credit</TD>\n"
    <<"</TR>\n\n";
}
