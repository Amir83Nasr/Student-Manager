#include "../include/Teacher.h"
#include "../include/Student.h"
#include "../include/Course.h"

// ———————————–––––––––––––––---(Teacher)----------------------------

// ——————————–––––––––––---------------------

json Teacher::toJSON() const
{
  return {
      {"id", id},
      {"password", password},
      {"firstName", firstName},
      {"lastName", lastName},
      {"birthYear", birthYear},
      {"birthMonth", birthMonth},
      {"birthDay", birthDay},
      {"courses", courses}};
}

// ——————————–––––––––––---------------------

Teacher Teacher::fromJSON(const json &j)
{
  Teacher teacher;

  teacher.id = j.at("id").get<string>();
  teacher.password = j.at("password").get<string>();
  teacher.firstName = j.at("firstName").get<string>();
  teacher.lastName = j.at("lastName").get<string>();
  teacher.birthYear = j.at("birthYear").get<int>();
  teacher.birthMonth = j.at("birthMonth").get<int>();
  teacher.birthDay = j.at("birthDay").get<int>();
  teacher.courses = j.at("courses").get<vector<string>>();

  return teacher;
}

// ————————————–––––––––––––––----------------------------------------