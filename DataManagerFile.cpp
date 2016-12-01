//
//  DataManagerFile.cpp
//  Project5
//
//  Created by Kyle Lei on 1/12/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "DataManager.h"
#include <iostream>
#include <fstream>

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
