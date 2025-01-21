#include "../include/Teacher.h"
#include "../include/Student.h"
#include "../include/Course.h"

// ———————————–––––––––––––––---(Teacher)----------------------------

void Teacehr::viewStudentsInCourse(const string &courseName, const vector<Student> &students) const
{
  cout << "\n═════════════════════════════════════════════════════\n";
  cout << " Students in Course: " << courseName << "\n";
  cout << "═════════════════════════════════════════════════════\n";
  cout << left << setw(15) << "Student ID" << setw(25) << "Name" << "\n";
  cout << "-----------------------------------------------------\n";
  for (const auto &student : students)
  {
    for (const auto &course : student.courses)
    {
      if (course.name == courseName)
      {
        cout << left << setw(15) << student.id << student.firstName << " " << student.lastName << "\n";
      }
    }
  }
  cout << "═════════════════════════════════════════════════════\n";
}

void Teacehr::modifyStudentGrade(const string &courseName, int studentID, double newGrade, vector<Student> &students) const
{
  for (auto &student : students)
  {
    if (student.id == studentID)
    {
      for (auto &course : student.courses)
      {
        if (course.name == courseName)
        {
          course.grade = newGrade;
          cout << "\n✅ Grade updated successfully for student " << studentID << " in course " << courseName << "!\n";
          return;
        }
      }
    }
  }
  cout << "\n❌ Student or course not found!\n";
}

void Teacehr::displayInfo() const
{
  cout << "\n═════════════════════════════════════════════════════\n";
  cout << " Teacher Information \n";
  cout << "═════════════════════════════════════════════════════\n";
  cout << "Name: " << firstName << " " << lastName << "\n";
  cout << "National ID: " << nationalID << "\n";
  cout << "═════════════════════════════════════════════════════\n";
}

// ————————————–––––––––––––––----------------------------------------