//
//  DataManagerHelper.cpp
//  Project5
//
//  Created by Kyle Lei on 30/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"

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
