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
    void teacherMenu(Teacher &teacher);

public:
    explicit Manager(const string &teacherFile, const string &studentFile, const string &courseFile);

    // ——————————–––––––––––---------------------

    void manageStudents();

    void showStudentDetails();
    void filterStudents();

    void addStudent();
    void editStudent();
    void deleteStudent();

    void saveStudentsToFileSorted() const;
    void loadStudentsFromFile();

    // ——————————–––––––––––---------------------

    void manageTeachers();

    void showTeacherDetails();

    void addTeacher();
    void editTeacher();
    void deleteTeacher();

    void saveTeachersToFileSorted() const;
    void loadTeachersFromFile();

    // ——————————–––––––––––---------------------

    void manageCourses();

    void addCourse();
    void editCourse();
    void deleteCourse();

    void saveCoursesToFileSorted() const;
    void loadCoursesFromFile();

    // ——————————–––––––––––---------------------

    void adminLogin();
    void teacherLogin();
    void studentLogin();

    void exportToExcel(const string &outputFilename) const;
    void run();
};

// ————————————–––––––––––––––----------------------------------------

#endif // MANAGER_H