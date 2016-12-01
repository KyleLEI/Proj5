//
//  Registration.h
//  Project5
//
//  Created by Kyle Lei on 27/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#ifndef Registration_h
#define Registration_h
#include "SortedList.h"
#include "Student.h"
#include "Course.h"

class Registration{
    Student* stu;
    Course* course;
    bool isGradeAssigned;
    double mark;
public:
    Registration(Student* in_stu,Course* in_course,bool in_assigned=false,double in_mark=0.0);
    
    Student* getStudent() const{return stu;}
    Course* getCourse() const{return course;}
    bool isGradeAvailable() const{return isGradeAssigned;}
    double getMark() const{return mark;}
    
    void assignMark(double in_mark){isGradeAssigned=true;mark=in_mark;};
    void removeMark(){isGradeAssigned=false;}
    
    
    bool operator>(const Registration& other);
    bool operator==(const Registration& other);
};

class RegistrationTable{
    SortedList<Registration> table;
public:
    RegistrationTable(){};
    Registration* addRegistration(const Registration& input){return table.insert(input);};
    Registration* findRegistration(const std::string stu_id, const std::string course_code);
    Node<Registration>* findRegistrationNode(const std::string stu_id, const std::string course_code);
    bool removeRegistration(const std::string stu_id, const std::string course_code);
    bool removeRegistrationNode(Node<Registration>*);
    bool queryRegistration(const std::string stu_id, const std::string course_code);
    
    SortedList<Registration>* getTable(){return &table;}
};
#endif /* Registration_h */
