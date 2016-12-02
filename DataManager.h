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
#include <fstream>

class DataManager{
    RegistrationTable regTable;
    StudentTable stuTable;
    CourseTable courseTable;
public:
    DataManager(){};
    int exec();
private:
    static void displayMainMenu();
    void displayStudentMenu();
    void displayCourseMenu();
    void displayRegMenu();
    void displayReportMenu();
    void displayFileMenu();
    void displayHTMMenu();
    
    void insertStudent();
    void insertCourse();
    void insertReg();
    
    void modifyStudent();
    void modifyCourse();
    void modifyMark();
    
    void queryStudent();
    void queryCourse();
    void queryReg();
    
    void deleteStudent();
    void deleteCourse();
    void deleteReg();
    
private:
    /*------helper functions------*/
    static inline bool isDigit(const char& input){return input>='0'&&input<='9';}//ASCII
    static inline bool isUpper(const char& input){return input>='A'&&input<='Z';}//ASCII
    static bool verifyStuID(const std::string&);
    static bool verifyStuName(const std::string&);
    static bool verifyStuYear(const int&);
    static bool verifyStuGender(const std::string&);
    static bool verifyCourseCode(const std::string&);
    static bool verifyCourseName(const std::string&);
    static bool verifyCredit(const int&);
    static bool verifyMark(const double&);
    static bool verifyChoice(const int&,const int&);
    
    static char charGender(const Student::Gender&);
    static std::string strGender(const Student::Gender&);
    
    static void waitForEnter();
    static bool readInput(std::string&);//returns true if only '\n' is input
    static bool readInput(int&);
    static bool readInput(double&);
    
    /*------file IO functions------*/
    void loadDB();
    void saveDB();
    
    void saveStudent(std::ofstream&, SortedList<Student>*);
    void saveCourse(std::ofstream&, SortedList<Course>*);
    void saveReg(std::ofstream&, SortedList<Registration>*);
    
    void loadStudent(std::ifstream&);
    void loadCourse(std::ifstream&);
    void loadReg(std::ifstream&);
    
    /*------HTML output functions------*/
    static void addHTMLStart(std::ofstream&,const std::string&,bool);
    static void addHTMLEnd(std::ofstream&,bool);
    
    void htmAllStudents();
    void htmAllCourses();
    void htmCourseOfStudent();
    void htmStudentOfCourse();
};

#endif /* DataManager_h */
