#ifndef MANAGER_H
#define MANAGER_H

#include "Utils.h"
#include "Student.h"
#include "Teacher.h"
#include "Course.h"

// ———————————–––––––––––––––(Classes)-------------------------------

class Manager
{
private:
    vector<Teacher> teachers;
    vector<Student> students;
    vector<Course> courses;

    const string teacherFilename;
    const string studentFilename;
    const string courseFilename;

    void accessMenu();
    void adminMenu();
    void studentMenu(Student &student);
    void teacherMenu();

public:
    explicit Manager(const string &teacherFile, const string &studentFile);

    void listStudents();
    void filterStudents();
    void showStudentDetails();

    void addStudent();
    void editStudent();
    void deleteStudent();

    void saveStudentsToFileSorted() const;
    void loadStudentsFromFile();

    void saveTeachersToFileSorted() const;
    void loadTeachersFromFile();

    void loadCoursesFromFile();
    void saveCoursesToFile();

    void exportToExcel(const string &outputFilename) const;

    void studentLogin();

    void run();
};

// ————————————–––––––––––––––----------------------------------------

#endif // MANAGER_H