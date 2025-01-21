#ifndef COURSE_H
#define COURSE_H

#include "Utils.h"
#include <vector>
#include <fstream>

// ———————————–––––––––––––––(Classes)-------------------------------

struct Course
{
  string code;       // کد درس
  string name;       // نام درس
  string instructor; // استاد درس

  double grade; // نمره
  int weight;   // وزن درس (معادل تعداد واحد)

  Course(const string &code = "", const string &name = "", const string &instructor = "", int weight = 0, double grade = 0.0);

  json toJSON() const;
  static Course fromJSON(const json &j);
};

#endif // COURSE_H
