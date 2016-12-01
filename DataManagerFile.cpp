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

using namespace std;

void DataManager::displayFileMenu(){
    system("clear");
    cout<<endl;
    cout<<"HKUST Course Registration System  (File Menu)\n"
    <<"---------------------------------------------\n"<<endl
    <<"1. Save Database\n"
    <<"2. Load Database\n"
    <<"3. Go back to main menu\n"<<endl
    <<"Enter your choice (1-3): ";
    
    int choice;
    readInput(choice);
    while(!verifyChoice(choice, 3)){
        cout<<"Invalid input, re-enter again (1-3): ";
        readInput(choice);
    }
    switch (choice) {
        case 1:
            saveDB();
            break;
            
        case 2:

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
        readInput(filename);
    }
    
    ofstream fout(filename);
    if(!fout.is_open()){
        cout<<"Error: Write File Error\n"<<endl;
        waitForEnter();
        return;
    }
    fout<<"Student: \n";
    saveStudent(fout, stuTable.getTable());
    fout<<"Course: \n";
    saveCourse(fout, courseTable.getTable());
    fout<<"Reg: \n";
    saveReg(fout, regTable.getTable());
    
    fout.close();
    cout<<"Successfully saved\n"<<endl;
    waitForEnter();
}
