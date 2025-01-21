#ifndef TEACHER_H
#define TEACHER_H

#include "Utils.h"
#include "Student.h"

// ———————————–––––––––––––––(Classes)-------------------------------

struct Teacher
{

    string id;
    string password;
    string firstName;
    string lastName;

    vector<string> courses;

    bool authenticate(const string &id, const string &pwd) const;

    void addCourse(const string &courseName);

    void viewStudentsInCourse(const string &courseName, const vector<Student> &students) const;

    void modifyStudentGrade(const string &courseName, int studentID, double newGrade, vector<Student> &students) const;

    void displayInfo() const;

    json toJSON() const;
    static Teacher fromJSON(const json &j);
};

// ————————————–––––––––––––––----------------------------------------

#endif // TEACHER_H