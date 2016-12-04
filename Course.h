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
    Course(){};
    Course(std::string in_code, std::string in_name, int in_credit):
    code(in_code),name(in_name),credit(in_credit){}
    
    std::string getCode() const{return code;}
    std::string getName() const{return name;}
    int getCredit() const{return credit;}
    SortedList<Registration*>* getEnrolledStudents() {return &ptrs;}
    bool removeLinkToReg(Registration* in_link){return ptrs.remove(in_link);}
    
    void setName(std::string in_name){name=in_name;}
    void setCredit(int in_cre){credit=in_cre;}
    
    void linkToReg(Registration* in_link){ptrs.insertRaw(in_link);}
    
    bool operator>(const Course& other){return this->code>other.code;}
    friend bool operator<(const Course& c1,const Course& c2){return c1.code<c2.code;}//overloaded for sort
    bool operator==(const Course& other){return this->code==other.code;}
    Course& operator=(const Course&);//overloaded for report generation
};

class CourseTable{
    enum{b=36,m=17};
    SortedList<Course> table[m];//array of linked list for hashing
public:
    CourseTable(){};
    void addCourse(const Course&);
    Course* findCourse(const std::string);
    Node<Course>* findCourseNode(const std::string);
    bool queryCourse(const std::string);
    bool removeCourseNode(Node<Course>*);
    SortedList<Course>* getTable(){return table;}
    int getBucketNum() const{return m;}
    int getSize() const;
    
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
