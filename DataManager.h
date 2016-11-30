//
//  DataManager.h
//  Project5
//
//  Created by Kyle Lei on 27/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#ifndef DataManager_h
#define DataManager_h
#include "Registration.h"
#include <string>

class FileManager{};
class OutputHandler{};
class DataManager{
    RegistrationTable regTable;
    StudentTable stuTable;
    CourseTable courseTable;
public:
    DataManager(){};
    int exec();
public:
    void displayStudentMenu();
    void displayCourseMenu();
    void displayRegMenu();
    
    void insertStudent();
    void insertCourse();
    void insertReg();
    
    void modifyStudent();
    void modifyCourse();
    
    void queryStudent();
    void queryCourse();
    void queryReg();
    
    void deleteStudent();
    void deleteCourse();
    void deleteReg();
    
    void modifyMark();
    
private:
    static inline bool isDigit(const char input){return input>='0'&&input<='9';}//ASCII
    static inline bool isUpper(const char input){return input>='A'&&input<='Z';}//ASCII
    static bool verifyStuID(const std::string);
    static bool verifyStuName(const std::string);
    static bool verifyStuYear(const int);
    static bool verifyStuGender(const std::string);
    static bool verifyCourseCode(const std::string);
    static bool verifyCourseName(const std::string);
    static bool verifyCredit(const int);
    static bool verifyMark(const double);
    
    static char charGender(Student::Gender);
    static std::string strGender(Student::Gender);
    
    static void waitForEnter();
    static bool readInput(std::string&);//returns true if only '\n' is input
    static bool readInput(int&);
};

#endif /* DataManager_h */
