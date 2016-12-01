//
//  Student.cpp
//  Project5
//
//  Created by Kyle Lei on 27/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "Student.h"
using namespace std;

StudentTable::StudentTable(const int numBuckets):m(numBuckets){
    for(int i=0;i<m;++i){
        SortedList<Student> temp;
        table.insertRaw(temp); //new secondary lists in primary list
    }
}

int StudentTable::hash(const Student& input){
    int sum=0;
    for(int i=0;i<input.getID().size();++i)
        sum+=input.getID()[i];//won't overflow since 99999999<2^31-1
    sum%=m;
    return sum;
}

void StudentTable::addStudent(const Student& stuToAdd){
    table[hash(stuToAdd)].insert(stuToAdd);
}

bool StudentTable::removeStudentNode(Node<Student>* node){
    return table[hash(node->content)].removeNode(node);
}

Student* StudentTable::findStudent(const std::string in_ID){
    Student stuToFind(in_ID, "", 0, Student::Male);
    Node<Student>* ptr=table[hash(stuToFind)].find(stuToFind);
    if(ptr!=NULL) return &ptr->content;
    return NULL;
}

Node<Student>* StudentTable::findStudentNode(const std::string in_ID){
    Student stuToFind(in_ID, "", 0, Student::Male);
    return table[hash(stuToFind)].find(stuToFind);
}

bool StudentTable::queryStudent(const std::string in_ID){
    Student stuToFind(in_ID, "", 0, Student::Male);
    return table[hash(stuToFind)].find(stuToFind)!=NULL;
}
