//
//  Course.h
//  Project5
//
//  Created by Kyle Lei on 27/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#ifndef Course_h
#define Course_h
#include <string>
#include "SortedList.h"

class Registration;

class Course{
    std::string code;
    std::string name;
    int credit;
    SortedList<Registration*> ptrs;
public:
    Course(std::string in_code, std::string in_name, int in_credit):
    code(in_code),name(in_name),credit(in_credit){}
    
    std::string getCode() const{return code;}
    std::string getName() const{return name;}
    int getCredit() const{return credit;}
    SortedList<Registration*>* getEnrolledStudents() {return &ptrs;}
    bool removeLinkToReg(Registration* in_link){return ptrs.remove(in_link);}
    
    void setCode(std::string in_code){code=in_code;}
    void setName(std::string in_name){name=in_name;}
    void setCredit(int in_cre){credit=in_cre;}
    
    void linkToReg(Registration* in_link){ptrs.insert(in_link);}
    
    bool operator>(const Course& other){return this->code>other.code;}
    bool operator==(const Course& other){return this->code==other.code;}
};

class CourseTable{
    SortedList<SortedList<Course> > table;
    const int m;
    enum{b=36};
public:
    CourseTable(const int=17);
    void addCourse(const Course&);
    Course* findCourse(const std::string);
    Node<Course>* findCourseNode(const std::string);
    bool queryCourse(const std::string);
    bool removeCourseNode(Node<Course>*);
private:
    int hash(const Course&);
    static inline bool isDigit(const char input){return input>='0'&&input<='9';}//ASCII
    inline int overflowSafeWeight(int i){
        int product=1;
        for (int j = 0; j < i; j++)
            product = (product * b) % m;
        return product;
    }
};

#endif /* Course_h */
