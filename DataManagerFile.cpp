//
//  DataManagerFile.cpp
//  Project5
//
//  Created by Kyle Lei on 1/12/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"
#include <iostream>
#include <cstdlib>

#define secretSequence "c9t508ecGU7Z6mEY9WJDlTPNnePA0GJ"
using namespace std;

void DataManager::displayFileMenu(){
    system("clear");
    cout<<"HKUST Course Registration System  (File Menu)\n"
    <<"---------------------------------------------\n"<<endl
    <<"1. Save Database\n"
    <<"2. Load Database\n"
    <<"3. Go back to main menu\n"<<endl
    <<"Enter your choice (1-3): ";
    
    int choice;
    readInput(choice);
    while(!verifyChoice(choice, 3)){
        cout<<"Invalid input, re-enter (1-3): ";
        readInput(choice);
    }
    switch (choice) {
        case 1:
            saveDB();
            break;
            
        case 2:
            loadDB();
            break;
            
        case 3:
            break;
    }
    
}

void DataManager::saveDB(){
    cout<<"Enter the filename: ";
    string filename;
    while(readInput(filename)){
        cout<<"Please enter a valid filename: ";
    }
    
    ofstream fout(filename);
    if(!fout.is_open()){
        cout<<"Error: Write File Error\n"<<endl;
        waitForEnter();
        return;
    }
    fout<<secretSequence<<"\n";//add a secret sequence to indicate file type
    saveStudent(fout, stuTable.getTable());
    fout<<char(29);
    saveCourse(fout, courseTable.getTable());
    fout<<char(29);
    saveReg(fout, regTable.getTable());
    fout<<char(29);
    fout.close();
    
    cout<<"Database successfully saved\n"<<endl;
    waitForEnter();
}

void DataManager::loadDB(){
    cout<<"Enter the filename: ";
    string filename;
    while(readInput(filename)){
        cout<<"Please enter a valid filename: ";
    }
    
    ifstream fin(filename);
    if(!fin.is_open()){
        cout<<"Error: Load File Error (File does not exist / File Corrupted)\n"<<endl;
        waitForEnter();
        return;
    }
    
    string sequence;
    fin>>sequence;
    if(sequence!=secretSequence){//verify the secret sequence, if match, the file type is correct
        cout<<"Error: Load File Error (Incorrect Format)\n"<<endl;
        waitForEnter();
        return;
    }
    fin.get();//get rid of the \n
    loadStudent(fin);
    loadCourse(fin);
    loadReg(fin);
    fin.close();
    
    cout<<"Database successfully loaded\n"<<endl;
    waitForEnter();
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
        
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        string in_ID=container;
        container.clear();
        
        if(stuTable.queryStudent(in_ID)){
            while(fin.get(c),c!=char(31)){}
            while(fin.get(c),c!=char(31)){}
            while(fin.get(c),c!=char(30)){}
            continue;
        }
        
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        string in_name=container;
        container.clear();
        
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        int in_year=atoi(container.c_str());
        container.clear();
        
        while(fin.get(c),c!=char(30)){
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
        
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        string in_code=container;
        container.clear();
        
        if(courseTable.queryCourse(in_code)){
            while(fin.get(c),c!=char(31)){}
            while(fin.get(c),c!=char(30)){}
            continue;
        }
        
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        string in_name=container;
        container.clear();
        
        while(fin.get(c),c!=char(30)){
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
        
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        string in_ID=container;
        Student* stuptr=stuTable.findStudent(in_ID);
        container.clear();
        
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        string in_code=container;
        Course* courseptr=courseTable.findCourse(in_code);
        container.clear();
        
        if(regTable.queryRegistration(in_ID, in_code)){
            while(fin.get(c),c!=char(31)){}
            while(fin.get(c),c!=char(30)){}
            continue;
        }
        while(fin.get(c),c!=char(31)){
            container.push_back(c);
        }
        bool isGrade;
        if(container=="0")isGrade=false;
        else isGrade=true;
        container.clear();
        
        while(fin.get(c),c!=char(30)){
            container.push_back(c);
        }
        double mark=atof(container.c_str());
        container.clear();
        
        Registration newReg(stuptr, courseptr,isGrade,mark);
        Registration* regaddr=regTable.addRegistration(newReg);
        stuptr->linkToReg(regaddr);
        courseptr->linkToReg(regaddr);
    }
}
