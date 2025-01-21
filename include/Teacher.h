#ifndef TEACHER_H
#define TEACHER_H

#include "Utils.h"
#include "Student.h"

// ———————————–––––––––––––––(Classes)-------------------------------

struct Teacher
{

    string nationalID;
    string password;
    string firstName;
    string lastName;

    vector<string> courses;

    Teacher(const string &id, const string &pwd, const string &first, const string &last)
        : nationalID(id), password(pwd), firstName(first), lastName(last) {}

    bool authenticate(const string &id, const string &pwd) const;

    void addCourse(const string &courseName);

    void viewStudentsInCourse(const string &courseName, const vector<Student> &students) const;

    void modifyStudentGrade(const string &courseName, int studentID, double newGrade, vector<Student> &students) const;

    void displayInfo() const;
};

// ————————————–––––––––––––––----------------------------------------

#endif // TEACHER_H