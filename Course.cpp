//
//  Course.cpp
//  Project5
//
//  Created by Kyle Lei on 27/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "Course.h"
#include <cmath>

CourseTable::CourseTable(const int numBuckets):m(numBuckets){
    for(int i=0;i<m;++i){
        SortedList<Course> temp;
        table.insertRaw(temp); //new secondary lists in primary list
    }
}

int CourseTable::hash(const Course& input){
    int sum=0;
    for(int i=0;i<input.getCode().size();++i){
        int ci;
        if(isDigit(input.getCode()[i])) ci=input.getCode()[i];
        else ci=input.getCode()[i]+10;
        sum=(sum+(ci*(overflowSafeWeight(i)%m))%m)%m;//need to prevent overflow since 36^7>2^31-1
    }
    return sum;
}

void CourseTable::addCourse(const Course& courseToAdd){
    table[hash(courseToAdd)].insert(courseToAdd);
}

bool CourseTable::removeCourseNode(Node<Course>* node){
    return table[hash(node->content)].removeNode(node);
}

Course* CourseTable::findCourse(const std::string in_code){
    Course courseToFind(in_code,"",0);
    Node<Course>* ptr=table[hash(courseToFind)].find(courseToFind);
    if(ptr!=NULL) return &ptr->content;
    return NULL;
}

Node<Course>* CourseTable::findCourseNode(const std::string in_code){
    Course courseToFind(in_code,"",0);
    return table[hash(courseToFind)].find(courseToFind);
}

bool CourseTable::queryCourse(const std::string in_code){
    Course courseToFind(in_code,"",0);
    return table[hash(courseToFind)].find(courseToFind)!=NULL;
}
