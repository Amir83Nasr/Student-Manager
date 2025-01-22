#ifndef STUDENT_H
#define STUDENT_H

#include "Utils.h"
#include "Course.h"

// ———————————–––––––––––––––(Classes)-------------------------------

struct Student
{
  string id;
  string firstName;
  string lastName;
  int entryYear;

  vector<Course> courses;

  // محاسبه مجموع وزن دروس
  int totalWeight() const;

  // محاسبه میانگین وزنی
  double averageGrade() const;

  json toJSON() const;
  static Student fromJSON(const json &j);
};

// ————————————–––––––––––––––----------------------------------------

#endif // STUDENT_H