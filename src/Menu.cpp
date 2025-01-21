#include "../include/Manager.h"
#include "../include/Student.h"
// #include "../include/Teacher.h"
#include "../include/Course.h"
#include "../include/Utils.h"

// ———————————–––––––––––––––(Function)-------------------------------

void Manager::studentMenu(Student &student)
{
  // loadStudentsFromFile();
  while (true)
  {
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           Student Menu                              ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝";

    cout
        << "\n╔══════════════════════════════════════════════════════════ Options ══╗\n";
    cout << "║ 1️⃣  test                                                             ║\n";
    cout << "║ 2️⃣  tset                                                             ║\n";
    cout << "║ 0️⃣  Logout                                                           ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    int choice;
    cout << "╔═════════════════════════════════════════════════════════════════════╗";
    cout << "\n║ Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      clearConsole();
      // listStudents();
      break;
    case 2:
      // exportToExcel("../data/students.csv");
      waitForKeyPress();
      break;
    case 0:
      // saveStudentsToFileSorted();

      cout << "╚═══════════════════════════════════════════════════════════ Logout ══╝\n";
      waitForKeyPress();
      return;
    default:
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
      cout << "║ ❌ Invalid choice. Please try again.                                ║\n";
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "═══════════════════════════════════════════════════════════════════════\n";
      waitForKeyPress();
    }
  }
}

// ——————————–––––––––––---------------------

void Manager::teacherMenu(Teacher &teacher)
{
  // loadStudentsFromFile();
  while (true)
  {
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           Teacher Menu                              ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝";

    cout
        << "\n╔══════════════════════════════════════════════════════════ Options ══╗\n";
    cout << "║ 1️⃣  test                                                             ║\n";
    cout << "║ 2️⃣  tset                                                             ║\n";
    cout << "║ 0️⃣  Logout                                                           ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    int choice;
    cout << "╔═════════════════════════════════════════════════════════════════════╗";
    cout << "\n║ Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      clearConsole();
      // listStudents();
      break;
    case 2:
      // exportToExcel("../data/students.csv");
      waitForKeyPress();
      break;
    case 0:
      // saveStudentsToFileSorted();

      cout << "╚═══════════════════════════════════════════════════════════ Logout ══╝\n";
      waitForKeyPress();
      return;
    default:
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
      cout << "║ ❌ Invalid choice. Please try again.                                ║\n";
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "═══════════════════════════════════════════════════════════════════════\n";
      waitForKeyPress();
    }
  }
}

// ——————————–––––––––––---------------------

void Manager::adminMenu()
{
  loadStudentsFromFile();
  while (true)
  {
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                            Admin Menu                               ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝";

    // منوی انتخاب گزینه‌ها
    cout
        << "\n╔══════════════════════════════════════════════════════════ Options ══╗\n";
    cout << "║ 1️⃣  Manage Students                                                  ║\n";
    cout << "║ 2️⃣  Manage Teachers                                                  ║\n";
    cout << "║ 3️⃣  Export to Excel                                                  ║\n";
    cout << "║ 0️⃣  Logout                                                           ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    int choice;
    cout << "╔═════════════════════════════════════════════════════════════════════╗";
    cout << "\n║ Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      clearConsole();
      listStudents();
      break;
    case 2:
      clearConsole();
      manageTeachers();
      break;
    case 3:
      exportToExcel("../data/students.csv");
      waitForKeyPress();
      break;
    case 0:
      saveStudentsToFileSorted();

      cout << "╚═══════════════════════════════════════════════════════════ Logout ══╝\n";
      waitForKeyPress();
      return;
    default:
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
      cout << "║ ❌ Invalid choice. Please try again.                                ║\n";
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "═══════════════════════════════════════════════════════════════════════\n";
      waitForKeyPress();
    }
  }
}

// ——————————–––––––––––---------------------

void Manager::accessMenu()
{
  loadStudentsFromFile();
  // loadTeachersFromFile();

  while (true)
  {
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║              Student Manager : Created By Amir83Nasr                ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝";

    // منوی انتخاب گزینه‌ها
    cout
        << "\n╔══════════════════════════════════════════════════════════ Options ══╗\n";
    cout << "║ 1️⃣  Admin Login                                                      ║\n";
    cout << "║ 2️⃣  Teacher Login                                                    ║\n";
    cout << "║ 3️⃣  Student Login                                                    ║\n";
    cout << "║ 0️⃣  Exit                                                             ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    int choice;
    cout << "╔═════════════════════════════════════════════════════════════════════╗";
    cout << "\n║ Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      clearConsole();
      adminMenu();
      break;
    case 2:
      clearConsole();
      teacherLogin();
      break;
    case 3:
      studentLogin();
      break;
    case 0:
      saveStudentsToFileSorted();
      // saveTeachersToFileSorted();

      cout << "╚═════════════════════════════════════════════════════════ Goodbye! ══╝\n";
      waitForKeyPress();
      return;
    default:
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
      cout << "║ ❌ Invalid choice. Please try again.                                ║\n";
      cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

      cout << "═══════════════════════════════════════════════════════════════════════\n";
      waitForKeyPress();
    }
  }
}

// ————————————–––––––––––––––----------------------------------------