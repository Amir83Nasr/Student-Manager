#include "../include/Teacher.h"
#include "../include/Student.h"
#include "../include/Course.h"

// ———————————–––––––––––––––---(Teacher)----------------------------

json Teacher::toJSON() const
{
  return {
      {"id", id},
      {"password", password},
      {"firstName", firstName},
      {"lastName", lastName},
      {"courses", courses}};
}

// ——————————–––––––––––---------------------

Teacher Teacher::fromJSON(const json &j)
{
  Teacher t;
  t.id = j.at("id").get<string>();
  t.password = j.at("password").get<string>();
  t.firstName = j.at("firstName").get<string>();
  t.lastName = j.at("lastName").get<string>();
  t.courses = j.at("courses").get<vector<string>>();
  return t;
}

// ————————————–––––––––––––––----------------------------------------