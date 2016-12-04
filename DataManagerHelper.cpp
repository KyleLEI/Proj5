//
//  DataManagerHelper.cpp
//  Project5
//
//  Created by Kyle Lei on 30/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"
#include <cstdlib>
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

char DataManager::charGender(const Student::Gender& g){
    if(g==Student::Male) return 'M';
    else return 'F';
}

string DataManager::strGender(const Student::Gender& g){
    if(g==Student::Male) return "Male";
    else return "Female";
}

bool DataManager::verifyStuID(const string& in_ID){
    if(in_ID.size()!=8) return false;
    for(int i=0;i<8;++i)
        if(!isDigit(in_ID[i])) return false;
    return true;
}

bool DataManager::verifyStuName(const string& in_name){
    return in_name.size()>=1&&in_name.size()<=32;
}

bool DataManager::verifyStuYear(const int& in_year){
    return in_year>=1&&in_year<=4;
}

bool DataManager::verifyStuGender(const string& g){
    return (g=="M"||g=="m"||g=="F"||g=="f");
}

bool DataManager::verifyCourseCode(const string& in_code){
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

bool DataManager::verifyCourseName(const string& in_name){
    return in_name.size()>=1&&in_name.size()<=50;
}

bool DataManager::verifyCredit(const int& in_credit){
    return in_credit>=0&&in_credit<=5;
}

bool DataManager::verifyMark(const double& in_mark){
    return in_mark>=0&&in_mark<=100;
}

bool DataManager::verifyChoice(const int& in,const int& range){
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
    while(cin.get(c),c!='\n') container.push_back(c);
    return false;
}

bool DataManager::readInput(int& container){
    container=0;
    string tmp;
    char c;
    cin.get(c);
    if(c=='\n') return true;
    tmp.push_back(c);
    while(cin.get(c),c!='\n') tmp.push_back(c);
    container=atoi(tmp.c_str());
    return false;
}

bool DataManager::readInput(double& container){
    container=0;
    string tmp;
    char c;
    cin.get(c);
    if(c=='\n') return true;
    tmp.push_back(c);
    while(cin.get(c),c!='\n') tmp.push_back(c);
    container=atof(tmp.c_str());
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

void DataManager::addHTMLStart(ofstream& fout, const string& title, const bool has_table){
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

void DataManager::addHTMLEnd(ofstream& fout, const bool has_table){
    if(has_table)fout<<"</TABLE>\n";
    fout<<"</P>\n"
    <<"</BODY>\n"
    <<"</HTML>\n";
}
