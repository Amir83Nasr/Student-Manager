#ifndef COURSE_H
#define COURSE_H

#include "Utils.h"

// ———————————–––––––––––––––(Classes)-------------------------------

struct Course
{
  string code;       // کد درس
  string name;       // نام درس
  string instructor; // استاد درس

  double grade; // نمره
  int weight;   // وزن درس (معادل تعداد واحد)

  json toJSON() const;
  static Course fromJSON(const json &j);
};

// ————————————–––––––––––––––----------------------------------------

#endif // COURSE_H
