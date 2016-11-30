//
//  DataManager.cpp
//  Project5
//
//  Created by Kyle Lei on 28/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int DataManager::exec(){return 0;}

char DataManager::charGender(Student::Gender g){
    if(g==Student::Male) return 'M';
    else return 'F';
}

string DataManager::strGender(Student::Gender g){
    if(g==Student::Male) return "Male";
    else return "Female";
}

bool DataManager::verifyStuID(const string in_ID){
    if(in_ID.size()!=8) return false;
    for(int i=0;i<8;++i)
        if(!isDigit(in_ID[i])) return false;
    return true;
}

bool DataManager::verifyStuName(const string in_name){
    return in_name.size()>=1&&in_name.size()<=32;
}

bool DataManager::verifyStuYear(const int in_year){
    return in_year>=1&&in_year<=3;//is it 3 or 4?
}

bool DataManager::verifyStuGender(const string g){
    return (g=="M"||g=="m"||g=="F"||g=="f");
}

bool DataManager::verifyCourseCode(const string in_code){
    if(!(in_code.size()==7||in_code.size()==8)) return false;
    for(int i=0;i<4;++i)
        if(!isUpper(in_code[i])) return false;
    for(int i=4;i<in_code.size();++i)
        if(!isDigit(in_code[i])) return false;
    return true;
}

bool DataManager::verifyCourseName(const string in_name){
    return in_name.size()>=1&&in_name.size()<=50;
}

bool DataManager::verifyCredit(const int in_credit){
    return in_credit>=0&&in_credit<=5;
}

bool DataManager::verifyMark(const double in_mark){
    return in_mark>=0&&in_mark<=100;
}

void DataManager::waitForEnter(){
    cout<<"Press ENTER to continue...";
    char c;
    while(cin.get(c)){if(c=='\n') break;}
}

bool DataManager::readInput(std::string& container){
    container.clear();
    char c;
    cin.get(c);
    if(c=='\n') return true;
    container.push_back(c);
    while(cin.get(c)&&c!='\n') container.push_back(c);
    return false;
}

bool DataManager::readInput(int& container){
    string tmp;
    char c;
    cin.get(c);
    if(c=='\n') return true;
    tmp.push_back(c);
    while(cin.get(c)&&c!='\n') tmp.push_back(c);
    const char* ctmp=tmp.c_str();
    sscanf(ctmp, "%d",&container);
    return false;
}

void DataManager::displayStudentMenu(){
    system("clear");
    cout<<"HKUST Course Registration System  (Student Menu)\n"
    <<"------------------------------------------------\n"<<endl
    <<"1. Insert Student Record\n"
    <<"2. Modify Student Record\n"
    <<"3. Delete Student Record\n"
    <<"4. Query Student Record\n"
    <<"5. Go back to main menu\n"<<endl
    <<"Enter your choice (1-5): ";
}

void DataManager::displayCourseMenu(){
    system("clear");
    cout<<"HKUST Course Registration System  (Course Menu)\n"
    <<"-----------------------------------------------\n"<<endl
    <<"1. Insert Course Record\n"
    <<"2. Modify Course Record\n"
    <<"3. Delete Course Record\n"
    <<"4. Query Course Record\n"
    <<"5. Go back to main menu\n"<<endl
    <<"Enter your choice (1-5): ";
}

void DataManager::displayRegMenu(){
    system("clear");
    cout<<"HKUST Course Registration System  (Registration Menu)\n"
    <<"-----------------------------------------------------\n"<<endl
    <<"1. Add Course\n"
    <<"2. Drop Course\n"
    <<"3. Modify Exam Mark\n"
    <<"4. Query Registration\n"
    <<"5. Go back to main menu\n"<<endl
    <<"Enter your choice (1-5): ";
}

void DataManager::insertStudent(){
    cout<<"Enter the student ID: ";
    string in_ID;
    readInput(in_ID);
    while(!verifyStuID(in_ID)){
        cout<<"Invalid Input, please re-enter [student ID]: ";
        readInput(in_ID);
    }
    if(stuTable.queryStudent(in_ID)){
        cout<<"Student already exists\n"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"Enter the student name: ";
    string in_name;
    readInput(in_name);
    while(!verifyStuName(in_name)){
        cout<<"Invalid Input, please re-enter [student name]: ";
        readInput(in_name);
    }
    
    cout<<"Enter the student year [1-3]: ";
    int in_year;
    readInput(in_year);
    while(!verifyStuYear(in_year)){
        cout<<"Invalid Input, please re-enter [student year]: ";
        readInput(in_year);
    }
    
    cout<<"Enter the student gender [M,F]: ";
    string in_gender;
    Student::Gender gender;
    readInput(in_gender);
    while(!verifyStuGender(in_gender)){
        cout<<"Invalid Input, please re-enter [student gender]: ";
        readInput(in_gender);
    }
    if(in_gender=="M"||in_gender=="m") gender=Student::Male;
    else gender=Student::Female;
    
    Student stuToAdd(in_ID,in_name,in_year,gender);
    stuTable.addStudent(stuToAdd);
    cout<<"Creation of student record successful\n"<<endl;
    waitForEnter();
}

void DataManager::modifyStudent(){
    cout<<"Enter the student ID: ";
    string in_ID;
    readInput(in_ID);
    while(!verifyStuID(in_ID)){
        cout<<"Invalid Input, please re-enter [student ID]: ";
        readInput(in_ID);
    }
    Student* stuptr=stuTable.findStudent(in_ID);
    if(stuptr==NULL) {
        cout<<"Student does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"Enter the student name (if no change, just press ENTER) ["<<stuptr->getName()<<"]: ";
    string in_name;
    if(readInput(in_name)) goto year;
    while(!verifyStuName(in_name)){
        cout<<"Invalid Input, please re-enter (if no change, just press ENTER) ["<<stuptr->getName()<<"]: ";
        if(readInput(in_name)) goto year;
    }
    stuptr->setName(in_name);
    
    
year:
    cout<<"Enter the student year (if no change, just press ENTER) ["<<stuptr->getYear()<<"]: ";
    int in_year;
    if(readInput(in_year)) goto gender;
    while(!verifyStuYear(in_year)){
        cout<<"Invalid Input, please re-enter (if no change, just press ENTER) ["<<stuptr->getYear()<<"]: ";
        if(readInput(in_year)) goto gender;
    }
    stuptr->setYear(in_year);
    
gender:
    cout<<"Enter the student gender (if no change, just press ENTER) ["<<charGender(stuptr->getGender())<<"]: ";
    string in_gender;
    Student::Gender gender;
    if(readInput(in_gender)) goto finish;
    while(!verifyStuGender(in_gender)){
        cout<<"Invalid Input, please re-enter (if no change, just press ENTER) ["<<charGender(stuptr->getGender())<<"]: ";
        if(readInput(in_gender)) goto finish;
    }
    if(in_gender=="M"||in_gender=="m") gender=Student::Male;
    else gender=Student::Female;
    stuptr->setGender(gender);
    
finish:
    cout<<"Modification of student record successful\n"<<endl;
    waitForEnter();
}

void DataManager::queryStudent(){
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
    
    cout<<"\nID:\t"<<stuptr->getID()<<endl<<"Name\t"<<stuptr->getName()<<endl;
    cout<<"Year\t"<<stuptr->getYear()<<endl<<"Gender:\t"<<strGender(stuptr->getGender())<<endl;
    
    cout<<endl;
    waitForEnter();
}

void DataManager::deleteStudent(){
    cout<<"Enter the student ID: ";
    string in_ID;
    readInput(in_ID);
    while(!verifyStuID(in_ID)){
        cout<<"Invalid Input, please re-enter [student ID]: ";
        readInput(in_ID);
    }
    Node<Student>* nodeptr=stuTable.findStudentNode(in_ID);
    if(nodeptr==NULL){cout<<"Student does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    //from reg, delete every registration by this student
    SortedList<Registration*>* regptr=nodeptr->content.getEnrolledCourses();
    for(int i=0;i<regptr->getSize();++i){
        string code=regptr->operator[](i)->getCourse()->getCode();
        Node<Registration>* regToRemove=regTable.findRegistrationNode(in_ID, code);
        regToRemove->content.getCourse()->removeLinkToReg(&regToRemove->content);
        regTable.removeRegistrationNode(regToRemove);
    }
    
    stuTable.removeStudentNode(nodeptr);
    cout<<"Deletion of student record successful\n"<<endl;
    waitForEnter();
}

void DataManager::insertReg(){
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
    }
    
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    Course* courseptr=courseTable.findCourse(in_code);
    if(courseptr==NULL){
        cout<<"Course does not exist\n"<<endl;
        waitForEnter();
    }
    
    Registration newReg(stuptr, courseptr);
    Registration* regaddr=regTable.addRegistration(newReg);
    stuptr->linkToReg(regaddr);
    courseptr->linkToReg(regaddr);
}



