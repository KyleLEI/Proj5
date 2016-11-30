//
//  Registration.cpp
//  Project5
//
//  Created by Kyle Lei on 27/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#include "Registration.h"

Registration::Registration(Student* in_stu,Course* in_course,bool in_assigned,double in_mark):
stu(in_stu),course(in_course),isGradeAssigned(in_assigned),mark(in_mark){}

bool Registration::operator>(const Registration& other){
    if(*stu>*other.stu) return true;
    if(*stu==*other.stu)
        if(*course>*other.course) return true;
    return false;
}

bool Registration::operator==(const Registration& other){
    return *course==*other.course && *stu==*other.stu;
}

Registration* RegistrationTable::findRegistration
(const std::string stu_id, const std::string course_code){
    Student s(stu_id, "", 0, Student::Male);
    Course c(course_code, "", 0);
    Registration temp(&s,&c);
    return &table.find(temp)->content;
}

Node<Registration>* RegistrationTable::findRegistrationNode
(const std::string stu_id, const std::string course_code){
    Student s(stu_id, "", 0, Student::Male);
    Course c(course_code, "", 0);
    Registration temp(&s,&c);
    return table.find(temp);
}

bool RegistrationTable::removeRegistration
(const std::string stu_id, const std::string course_code){
    Student s(stu_id, "", 0, Student::Male);
    Course c(course_code, "", 0);
    Registration temp(&s,&c);
    return table.remove(temp);
}

bool RegistrationTable::removeRegistrationNode
(Node<Registration>* node){
    return table.removeNode(node);
}
