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

    // سال تولد به شمسی
    int birthYear = 0;
    int birthMonth = 0;
    int birthDay = 0;

    vector<string> courses;

    json toJSON() const;
    static Teacher fromJSON(const json &j);
};

// ————————————–––––––––––––––----------------------------------------

#endif // TEACHER_H