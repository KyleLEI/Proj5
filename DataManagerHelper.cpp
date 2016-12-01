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

void DataManager::saveStudent(ofstream& fout, SortedList<SortedList<Student> >* stuToSave){
    for(int i=0;i<stuToSave->getSize();++i){
        SortedList<Student>* list=&stuToSave->operator[](i);
        for(int j=0;j<list->getSize();++j){
            Student* stuptr=&list->operator[](j);
            fout<<stuptr->getID()<<" "<<stuptr->getName()<<" ";
            fout<<stuptr->getYear()<<" "<<static_cast<int>(stuptr->getGender())<<char(30);
        }
    }
}

void DataManager::saveCourse(ofstream& fout, SortedList<SortedList<Course> >* courseToSave){
    for(int i=0;i<courseToSave->getSize();++i){
        SortedList<Course>* list=&courseToSave->operator[](i);
        for(int j=0;j<list->getSize();++j){
            Course* ptr=&list->operator[](j);
            fout<<ptr->getCode()<<" "<<ptr->getName()<<" ";
            fout<<ptr->getCredit()<<char(30);
        }
    }
}

void DataManager::saveReg(std::ofstream& fout, SortedList<Registration>* regToSave){
    for(int i=0;i<regToSave->getSize();++i){
        Registration* reg=&regToSave->operator[](i);
        fout<<reg->getStudent()->getID()<<" "<<reg->getCourse()->getCode()<<" ";
        fout<<reg->isGradeAvailable()<<" "<<reg->getMark()<<char(30);
    }
}
