//
//  Student.h
//  Project5
//
//  Created by Kyle Lei on 27/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#ifndef Student_h
#define Student_h
#include <string>
#include "SortedList.h"

class Registration;

class Student{
    std::string ID;
    std::string name;
    int year;
    SortedList<Registration*> ptrs;
public:
    enum Gender{Male=0, Female};
    Student(std::string in_ID, std::string in_name, int in_year, Gender in_gender):
    ID(in_ID),name(in_name),year(in_year),gender(in_gender){};
    
    std::string getID() const{return ID;}
    std::string getName() const{return name;}
    int getYear() const{return year;}
    Gender getGender() const{return gender;}
    SortedList<Registration*>* getEnrolledCourses() {return &ptrs;}
    bool removeLinkToReg(Registration* in_link){return ptrs.remove(in_link);}
    
    void setID(std::string in_ID){ID=in_ID;}
    void setName(std::string in_name){name=in_name;}
    void setYear(int in_year){year=in_year;}
    void setGender(Gender in_g){gender=in_g;}
    
    void linkToReg(Registration* in_link){ptrs.insertRaw(in_link);}
    
    bool operator>(const Student& other){return this->ID>other.ID;}
    bool operator==(const Student& other){return this->ID==other.ID;}
private:
    Gender gender;
};

class StudentTable{
    enum{m=29};
    SortedList<Student> table[m];
public:
    StudentTable(){};
    void addStudent(const Student&);
    bool removeStudentNode(Node<Student>*);
    Student* findStudent(const std::string);
    Node<Student>* findStudentNode(const std::string);
    bool queryStudent(const std::string);
    SortedList<Student>* getTable(){return table;}
    int getBucketNum() const{return m;}
    bool isEmpty() const;
private:
    int hash(const Student&);
};

#endif /* Student_h */
