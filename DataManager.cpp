//
//  DataManager.cpp
//  Project5
//
//  Created by Kyle Lei on 28/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void DataManager::displayStudentMenu(){
    system("clear");
    cout<<endl;
    cout<<"HKUST Course Registration System  (Student Menu)\n"
    <<"------------------------------------------------\n"<<endl
    <<"1. Insert Student Record\n"
    <<"2. Modify Student Record\n"
    <<"3. Delete Student Record\n"
    <<"4. Query Student Record\n"
    <<"5. Go back to main menu\n"<<endl
    <<"Enter your choice (1-5): ";
    
    int choice;
    readInput(choice);
    while(!verifyChoice(choice, 5)){
        cout<<"Invalid input, re-enter again (1-5): ";
        readInput(choice);
    }
    switch (choice) {
        case 1:
            insertStudent();
            break;
            
        case 2:
            modifyStudent();
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
    
    cout<<"\nID:\t"<<stuptr->getID()<<endl<<"Name:\t"<<stuptr->getName()<<endl;
    cout<<"Year:\t"<<stuptr->getYear()<<endl<<"Gender:\t"<<strGender(stuptr->getGender())<<endl;
    
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

void DataManager::displayCourseMenu(){
    system("clear");
    cout<<endl;
    cout<<"HKUST Course Registration System  (Course Menu)\n"
    <<"-----------------------------------------------\n"<<endl
    <<"1. Insert Course Record\n"
    <<"2. Modify Course Record\n"
    <<"3. Delete Course Record\n"
    <<"4. Query Course Record\n"
    <<"5. Go back to main menu\n"<<endl
    <<"Enter your choice (1-5): ";
    
    int choice;
    readInput(choice);
    while(!verifyChoice(choice, 5)){
        cout<<"Invalid input, re-enter again (1-5): ";
        readInput(choice);
    }
    switch (choice) {
        case 1:
            insertCourse();
            break;
            
        case 2:
            modifyCourse();
            break;
            
        case 3:
            deleteCourse();
            break;
            
        case 4:
            queryCourse();
            break;
            
        case 5:
            break;
    }
}

void DataManager::insertCourse(){
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    if(courseTable.queryCourse(in_code)){
        cout<<"Course already exists\n"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"Enter the course name: ";
    string in_name;
    readInput(in_name);
    while(!verifyCourseName(in_name)){
        cout<<"Invalid Input, please re-enter [course name]: ";
        readInput(in_name);
    }
    
    cout<<"Enter the course credit [0-5]: ";
    int in_credit;
    readInput(in_credit);
    while(!verifyCredit(in_credit)){
        cout<<"Invalid Input, please re-enter [course credit]: ";
        readInput(in_credit);
    }
    
    Course courseToAdd(in_code,in_name,in_credit);
    courseTable.addCourse(courseToAdd);
    cout<<"Creation of course record successful\n"<<endl;
    waitForEnter();
}

void DataManager::queryCourse(){
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
    
    cout<<"\nCode:\t"<<ptr->getCode()<<endl<<"Name:\t"<<ptr->getName()<<endl;
    cout<<"Credit:\t"<<ptr->getCredit()<<endl;
    
    cout<<endl;
    waitForEnter();
}

void DataManager::modifyCourse(){
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    Course* ptr=courseTable.findCourse(in_code);
    
    if(ptr==NULL) {
        cout<<"Course does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"Enter the course name (if no change, just press ENTER) ["<<ptr->getName()<<"]: ";
    string in_name;
    if(readInput(in_name)) goto credit;
    while(!verifyCourseName(in_name)){
        cout<<"Invalid Input, please re-enter (if no change, just press ENTER) ["<<ptr->getName()<<"]: ";
        if(readInput(in_name)) goto credit;
    }
    ptr->setName(in_name);
    
    
credit:
    cout<<"Enter the credit (if no change, just press ENTER) ["<<ptr->getCredit()<<"]: ";
    int in_credit;
    if(readInput(in_credit)) goto finish;
    while(!verifyCredit(in_credit)){
        cout<<"Invalid Input, please re-enter (if no change, just press ENTER) ["<<ptr->getCredit()<<"]: ";
        if(readInput(in_credit)) goto finish;
    }
    ptr->setCredit(in_credit);
    
finish:
    cout<<"Modification of course record successful\n"<<endl;
    waitForEnter();
}

void DataManager::deleteCourse(){
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    Node<Course>* nodeptr=courseTable.findCourseNode(in_code);
    if(nodeptr==NULL){cout<<"Course does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    //from reg, delete every registration by this student
    SortedList<Registration*>* regptr=nodeptr->content.getEnrolledStudents();
    for(int i=0;i<regptr->getSize();++i){
        string ID=regptr->operator[](i)->getStudent()->getID();
        Node<Registration>* regToRemove=regTable.findRegistrationNode(ID, in_code);
        regToRemove->content.getStudent()->removeLinkToReg(&regToRemove->content);
        regTable.removeRegistrationNode(regToRemove);
    }
    
    courseTable.removeCourseNode(nodeptr);
    cout<<"Deletion of course record successful\n"<<endl;
    waitForEnter();
}

void DataManager::displayRegMenu(){
    system("clear");
    cout<<endl;
    cout<<"HKUST Course Registration System  (Registration Menu)\n"
    <<"-----------------------------------------------------\n"<<endl
    <<"1. Enroll Course\n"
    <<"2. Drop Course\n"
    <<"3. Modify Exam Mark\n"
    <<"4. Query Registration\n"
    <<"5. Go back to main menu\n"<<endl
    <<"Enter your choice (1-5): ";
    
    int choice;
    readInput(choice);
    while(!verifyChoice(choice, 5)){
        cout<<"Invalid input, re-enter again (1-5): ";
        readInput(choice);
    }
    switch (choice) {
        case 1:
            insertReg();
            break;
            
        case 2:
            deleteReg();
            break;
            
        case 3:
            modifyMark();
            break;
            
        case 4:
            queryReg();
            break;
            
        case 5:
            break;
    }
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
        return;
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
        return;
    }
    
    if(regTable.queryRegistration(in_ID, in_code)){
        cout<<"The student already registered the course\n"<<endl;
        waitForEnter();
        return;
    }
    Registration newReg(stuptr, courseptr);
    Registration* regaddr=regTable.addRegistration(newReg);
    stuptr->linkToReg(regaddr);
    courseptr->linkToReg(regaddr);
    cout<<"Enroll course successful\n"<<endl;
    waitForEnter();
}

void DataManager::deleteReg(){
    cout<<"Enter the student ID: ";
    string in_ID;
    readInput(in_ID);
    while(!verifyStuID(in_ID)){
        cout<<"Invalid Input, please re-enter [student ID]: ";
        readInput(in_ID);
    }
    if(!stuTable.queryStudent(in_ID)){
        cout<<"Student does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    if(courseTable.queryCourse(in_code)){
        cout<<"Course does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    Node<Registration>* regNode=regTable.findRegistrationNode(in_ID, in_code);
    if(regNode==NULL){
        cout<<"Registration not found"<<endl;
        waitForEnter();
        return;
    }
    regNode->content.getStudent()->removeLinkToReg(&regNode->content);
    regNode->content.getCourse()->removeLinkToReg(&regNode->content);
    cout<<"Drop course successful\n"<<endl;
    waitForEnter();
}

void DataManager::modifyMark(){
    cout<<"Enter the student ID: ";
    string in_ID;
    readInput(in_ID);
    while(!verifyStuID(in_ID)){
        cout<<"Invalid Input, please re-enter [student ID]: ";
        readInput(in_ID);
    }
    if(!stuTable.queryStudent(in_ID)){
        cout<<"Student does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    if(!courseTable.queryCourse(in_code)){
        cout<<"Course does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    Registration* reg=regTable.findRegistration(in_ID, in_code);
    if(reg==NULL){
        cout<<"Registration not found"<<endl;
        waitForEnter();
        return;
    }
    
    double in_mark;
    if(!reg->isGradeAvailable()){
        cout<<"Enter the exam mark [0-100]: ";
        readInput(in_mark);
        while(!verifyMark(in_mark)){
            cout<<"Invalid Input, please re-enter [exam mark]: ";
            readInput(in_mark);
        }
    }
    else{
        cout<<"Enter the exam mark (if no change, just press ENTER) ["<<reg->getMark()<<"]: ";
        if(readInput(in_mark)) goto finish;
        while(!verifyMark(in_mark)){
            cout<<"Invalid Input, please re-enter (if no change, just press ENTER) ["<<reg->getMark()<<"]: ";
            if(readInput(in_mark)) goto finish;
        }
    }
    reg->assignMark(in_mark);
finish:
    cout<<"Modification of exam mark successful\n"<<endl;
    waitForEnter();
}

void DataManager::queryReg(){
    cout<<"Enter the student ID: ";
    string in_ID;
    readInput(in_ID);
    while(!verifyStuID(in_ID)){
        cout<<"Invalid Input, please re-enter [student ID]: ";
        readInput(in_ID);
    }
    if(!stuTable.queryStudent(in_ID)){
        cout<<"Student does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"Enter the course code: ";
    string in_code;
    readInput(in_code);
    while(!verifyCourseCode(in_code)){
        cout<<"Invalid Input, please re-enter [course code]: ";
        readInput(in_code);
    }
    if(!courseTable.queryCourse(in_code)){
        cout<<"Course does not exist\n"<<endl;
        waitForEnter();
        return;
    }
    
    Registration* reg=regTable.findRegistration(in_ID, in_code);
    if(reg==NULL){
        cout<<"Registration not found"<<endl;
        waitForEnter();
        return;
    }
    
    cout<<"\nStudent ID:\t"<<reg->getStudent()->getID()<<endl;
    cout<<"Course Code:\t"<<reg->getCourse()->getCode()<<endl;
    cout<<"Exam Mark:\t";
    if(reg->isGradeAvailable()) cout<<reg->getMark()<<endl;
    else cout<<"Not Assigned"<<endl;
    
    cout<<endl;
    waitForEnter();
}
