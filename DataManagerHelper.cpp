//
//  DataManagerHelper.cpp
//  Project5
//
//  Created by Kyle Lei on 30/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int DataManager::exec(){
    while(true){
        displayMainMenu();
        int choice;
        readInput(choice);
        while(!verifyChoice(choice, 6)){
            cout<<"Invalid input, re-enter again (1-6): ";
            readInput(choice);
        }
        switch(choice){
            case 1:
                displayStudentMenu();
                break;
            case 2:
                displayCourseMenu();
                break;
            case 3:
                displayRegMenu();
                break;
            case 4:
                displayHTMMenu();
                break;
            case 5:
                displayFileMenu();
                break;
            case 6:
                return 0;
        }
    }
    return 0;
}

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
    return in_year>=1&&in_year<=4;
}

bool DataManager::verifyStuGender(const string g){
    return (g=="M"||g=="m"||g=="F"||g=="f");
}

bool DataManager::verifyCourseCode(const string in_code){
    if(!(in_code.size()==8||in_code.size()==9)) return false;
    for(int i=0;i<4;++i)
        if(!isUpper(in_code[i])) return false;
    for(int i=4;i<8;++i)
        if(!isDigit(in_code[i])) return false;
    if(in_code.size()==9){
        if(!isUpper(in_code[8])) return false;
    }
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

bool DataManager::verifyChoice(const int in,const int range){
    return in>=1&&in<=range;
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
    container=0;
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

bool DataManager::readInput(double& container){
    container=0;
    string tmp;
    char c;
    cin.get(c);
    if(c=='\n') return true;
    tmp.push_back(c);
    while(cin.get(c)&&c!='\n') tmp.push_back(c);
    const char* ctmp=tmp.c_str();
    sscanf(ctmp, "%lf",&container);
    return false;
}

void DataManager::displayMainMenu(){
    system("clear");
    cout<<"HKUST Course Registration System\n"
    <<"--------------------------------\n"<<endl
    <<"1. Student Management\n"
    <<"2. Course Management\n"
    <<"3. Course Registration\n"
    <<"4. Report Management\n"
    <<"5. File Management\n"
    <<"6. Exit\n"<<endl
    <<"Enter your choice (1-6): ";
}

void DataManager::saveStudent(ofstream& fout, SortedList<Student>* stuToSave){
    for(int i=0;i<stuTable.getBucketNum();++i){
        for(int j=0;j<stuToSave[i].getSize();++j){
            Student* stuptr=&stuToSave[i][j];
            fout<<stuptr->getID()<<char(31)<<stuptr->getName()<<char(31);
            fout<<stuptr->getYear()<<char(31)<<static_cast<int>(stuptr->getGender())<<char(30);
        }
    }
}

void DataManager::saveCourse(ofstream& fout, SortedList<Course>* courseToSave){
    for(int i=0;i<courseTable.getBucketNum();++i){
        for(int j=0;j<courseToSave[i].getSize();++j){
            Course* ptr=&courseToSave[i][j];
            fout<<ptr->getCode()<<char(31)<<ptr->getName()<<char(31);
            fout<<ptr->getCredit()<<char(30);
        }
    }
}

void DataManager::saveReg(std::ofstream& fout, SortedList<Registration>* regToSave){
    for(int i=0;i<regToSave->getSize();++i){
        Registration* reg=&regToSave->operator[](i);
        fout<<reg->getStudent()->getID()<<char(31)<<reg->getCourse()->getCode()<<char(31);
        fout<<reg->isGradeAvailable()<<char(31)<<reg->getMark()<<char(30);
    }
}

void DataManager::loadStudent(ifstream& fin){
    char c=0;
    string container;
    while(true){
        fin.get(c);
        if(c==char(29)) break;
        container.push_back(c);
        
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        string in_ID=container;
        container.clear();
        
        if(stuTable.queryStudent(in_ID)) continue;
        
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        string in_name=container;
        container.clear();
        
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        int in_year=atoi(container.c_str());
        container.clear();

        while(fin.get(c)&&c!=char(30)){
            container.push_back(c);
        }
        int in_gender=atoi(container.c_str());
        Student::Gender gender;
        if(in_gender==static_cast<int>(Student::Male)){gender=Student::Male;}
        else gender=Student::Female;
        container.clear();
        
        Student stuToAdd(in_ID, in_name, in_year, gender);
        stuTable.addStudent(stuToAdd);
    }
}

void DataManager::loadCourse(ifstream& fin){
    char c=0;
    string container;
    while(true){
        fin.get(c);
        if(c==char(29)) break;
        container.push_back(c);
        
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        string in_code=container;
        container.clear();
        
        if(courseTable.queryCourse(in_code)) continue;
        
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        string in_name=container;
        container.clear();
        
        while(fin.get(c)&&c!=char(30)){
            container.push_back(c);
        }
        int in_cre=atoi(container.c_str());
        container.clear();

        Course courseToAdd(in_code,in_name,in_cre);
        courseTable.addCourse(courseToAdd);
    }
}

void DataManager::loadReg(ifstream& fin){
    char c=0;
    string container;
    while(true){
        fin.get(c);
        if(c==char(29)) break;
        container.push_back(c);
        
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        string in_ID=container;
        Student* stuptr=stuTable.findStudent(in_ID);
        container.clear();
        
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        string in_code=container;
        Course* courseptr=courseTable.findCourse(in_code);
        container.clear();
        
        if(regTable.queryRegistration(in_ID, in_code)) continue;
        while(fin.get(c)&&c!=char(31)){
            container.push_back(c);
        }
        bool isGrade;
        if(container=="0")isGrade=false;
        else isGrade=true;
        container.clear();
        
        while(fin.get(c)&&c!=char(30)){
            container.push_back(c);
        }
        int mark=atoi(container.c_str());
        container.clear();
        
        Registration newReg(stuptr, courseptr,isGrade,mark);
        Registration* regaddr=regTable.addRegistration(newReg);
        stuptr->linkToReg(regaddr);
        courseptr->linkToReg(regaddr);
    }
}

void DataManager::addHTMLStart(ofstream& fout, string title, bool has_table){
    fout<<"<HTML>\n"
    <<"<HEAD>\n"
    <<"<TITLE>"<<title<<"</TITLE>\n"
    <<"</HEAD>\n"
    <<"<BODY bgColor=#ffffcc>\n"
    <<"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
    <<"<H2>"<<title<<"</H2>\n"
    <<"<P>\n";
    if(has_table)fout<<"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n";
}

void DataManager::addHTMLEnd(ofstream& fout,bool has_table){
    if(has_table)fout<<"</TABLE>\n";
    fout<<"</P>\n"
    <<"</BODY>\n"
    <<"</HTML>\n";
}
