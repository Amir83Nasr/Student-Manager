#include "../include/Manager.h"
#include "../include/Student.h"
#include "../include/Teacher.h"
#include "../include/Course.h"
#include "../include/Utils.h"

// ———————————–––––––––––––––(Manager)------------------------

Manager::Manager(const string &teacherFile, const string &studentFile, const string &courseFile) : teacherFilename(teacherFile), studentFilename(studentFile), courseFilename(courseFile) {}

void Manager::addStudent()
{
    Student s;
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           📋 Add Student                            ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═══════════════════════════════════════════════════════ informaion ══╗\n";

    // وارد کردن آیدی دانش‌آموز
    while (true)
    {
        cout << "║ Enter Student ID: ";
        bool idExists = false;

        while (!(cin >> s.id))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "║ ❌ Invalid input. Enter a valid integer for Student ID: ";
        }

        // بررسی تکراری بودن آیدی
        for (const auto &student : students)
        {
            if (student.id == s.id)
            {
                idExists = true;
                break;
            }
        }

        if (idExists)
        {
            cout << "║ ❌ This ID is already registered. Please enter a different ID.\n";
        }
        else
        {
            break; // آیدی معتبر است و تکراری نیست
        }
    }

    cin.ignore();

    // وارد کردن اطلاعات عمومی
    cout << "║ Enter First Name: ";
    getline(cin, s.firstName);
    cout << "║ Enter Last Name: ";
    getline(cin, s.lastName);

    // بررسی مقدار سال ورود
    cout << "║ Enter Entry Year (between 1398 and " << currentYear() << "): ";
    while (!(cin >> s.entryYear) || s.entryYear < 1398 || s.entryYear > currentYear())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a year between 1398 and " << currentYear() << ": ";
    }

    // تعداد دروس
    cout << "║ Enter Number of Courses: ";
    int count;
    while (!(cin >> count) || count < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a non-negative integer for Number of Courses: ";
    }
    s.courses.resize(count);

    // اطلاعات هر درس
    for (int i = 0; i < count; ++i)
    {
        cout << "║ - Enter Course Name: ";
        cin >> ws;
        getline(cin, s.courses[i].name);

        cout << "║ - Enter Course Weight (1-3): ";
        while (!(cin >> s.courses[i].weight) || s.courses[i].weight < 1 || s.courses[i].weight > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "║   ❌ Invalid input. Enter a weight between 1 and 3: ";
        }

        cout << "║ - Enter Course Grade (0-100): ";
        while (!(cin >> s.courses[i].grade) || s.courses[i].grade < 0 || s.courses[i].grade > 100)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "║   ❌ Invalid input. Enter a grade between 0 and 100: ";
        }
    }

    // اضافه کردن دانش‌آموز به لیست
    students.push_back(s);

    // نمایش پیام موفقیت
    cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ ✅ Student '" << s.firstName << " " << s.lastName << "' added successfully!\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "═══════════════════════════════════════════════════════════════════════\n";
    waitForKeyPress();
}

void Manager::showStudentDetails()
{
    cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                      View Student Informations                      ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ Enter Student ID to View: ";

    int id;
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a valid integer for Student ID: ";
    }

    // پیدا کردن دانش‌آموز
    auto it = find_if(students.begin(), students.end(), [id](const Student &s)
                      { return s.id == id; });

    if (it != students.end())
    {
        clearConsole();
        const Student &student = *it;

        // هدر
        cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                          Student Details                            ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        // اطلاعات دانش‌آموز
        cout << "╔══════════════════════════════════════════════════════ Information ══╗\n";
        cout << "║ ID          : " << setw(54) << left << student.id << "║\n";
        cout << "║ First Name  : " << setw(54) << left << student.firstName << "║\n";
        cout << "║ Last Name   : " << setw(54) << left << student.lastName << "║\n";
        cout << "║ Entry Year  : " << setw(54) << left << student.entryYear << "║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        if (student.courses.empty())
        {
            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ⚠️  No courses found for this student!                               ║\n";
        }
        else
        {
            // نمایش اطلاعات درس‌ها
            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║                           Courses Details                           ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ " << setw(22) << left << "Course Name" << setw(12) << left << "Weight"
                 << setw(12) << left << "Grade" << "                      ║\n";
            cout << "╠═════════════════════════════════════════════════════════════════════╣\n";
        }

        for (const auto &course : student.courses)
        {
            cout << "║ " << setw(24) << left << course.name
                 << setw(11) << left << course.weight
                 << setw(12) << left << fixed << setprecision(2) << course.grade << "                     ║\n";
        }

        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }
    else
    {
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Operation canceled. The student was not deleted.                 ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }

    cout << "═══════════════════════════════════════════════════════════════════════\n";
    waitForKeyPress();
}

void Manager::manageStudents()
{
    while (true)
    {
        loadStudentsFromFile();

        // هدر لیست دانش‌آموزان
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                     📝 Student List                                      ║\n";
        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // ستون‌های جدول
        cout << "║ " << left << setw(14) << "🔢 ID"
             << setw(25) << "👤 First Name"
             << setw(22) << "👥 Last Name"
             << setw(12) << "📅 Year"
             << setw(17) << "📊 Avg Grade"
             << setw(8) << "Weights" << " ║\n";

        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // اطلاعات دانش‌آموزان
        for (const auto &s : students)
        {
            cout << "║ " << left << setw(13) << s.id
                 << setw(23) << s.firstName
                 << setw(20) << s.lastName
                 << setw(13) << s.entryYear
                 << setw(15) << fixed << setprecision(2) << s.averageGrade()
                 << setw(4) << s.totalWeight() << " ║\n";
        }

        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n";

        // منوی انتخاب گزینه‌ها
        cout << "\n╔═══════════════════════════════════════════════════════ 📋 Options ══╗\n";
        cout << "║ 1️⃣  Add a Student                                                    ║\n";
        cout << "║ 2️⃣  Edit a Student                                                   ║\n";
        cout << "║ 3️⃣  Delete a Student                                                 ║\n";
        cout << "║ 4️⃣  View Student Details                                             ║\n";
        cout << "║ 5️⃣  Filter Students                                                  ║\n";
        cout << "║ 0️⃣  Return to Main Menu                                              ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        int option;
        cout << "╔" << "═════════════════════════════════════════════════════════════════════" << "╗";
        cout << "\n║ Your Choice: ";
        while (!(cin >> option) || option < 0 || option > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "║ ❌ Invalid choice. Enter a number between ( 0 and 5 ): ";
        }

        if (option != 0)
        {
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }

        switch (option)
        {
        case 1:
            clearConsole();
            addStudent();
            saveStudentsToFileSorted();
            break;
        case 2:
            editStudent();
            saveStudentsToFileSorted();
            break;
        case 3:
            deleteStudent();
            saveStudentsToFileSorted();
            break;
        case 4:
            showStudentDetails();
            break;
        case 5:
            filterStudents();
            break;
        case 0:
            cout << "╚═══════════════════════════════════════════════════ Return to Menu ══╝\n";

            waitForKeyPress();
            return;
        default:
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ❌ Invalid choice. Please try again.                                ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "═══════════════════════════════════════════════════════════════════════\n";
            waitForKeyPress();
            break;
        }
    }
}

void Manager::editStudent()
{
    cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                             Edit Student                            ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ Enter Student ID to Edit: ";

    int id;
    // بررسی ورودی معتبر
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a valid integer for Student ID: ";
    }

    // پیدا کردن دانش‌آموز
    auto it = find_if(students.begin(), students.end(), [id](const Student &s)
                      { return s.id == id; });

    if (it != students.end())
    {
        clearConsole();
        Student &s = *it;

        cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                             Edit Student                            ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        cout << "╔══════════════════════════════════════════════════════ Information ══╗\n";
        cout << "║ - ID: " << s.id << "                                                \n";
        cout << "║ - Name: " << s.firstName << " " << s.lastName << "                  \n";
        cout << "║ - Entry Year: " << s.entryYear << "                                \n";
        cout << "╠═════════════════════════════════════════════════════════════════════╣\n";

        string input;
        cin.ignore();

        // ویرایش نام
        cout << "║ Enter New First Name (current: " << s.firstName << "): ";
        getline(cin, input);
        if (!input.empty())
            s.firstName = input;

        cout << "║ Enter New Last Name (current: " << s.lastName << "): ";
        getline(cin, input);
        if (!input.empty())
            s.lastName = input;

        // ویرایش سال ورود
        cout << "║ Enter New Entry Year between 1398 and " << currentYear() << " (current: " << s.entryYear << "): ";
        while (true)
        {
            getline(cin, input);
            if (input.empty())
                break;
            try
            {
                int year = stoi(input);
                if (year > 1398 && year <= currentYear())
                {
                    s.entryYear = year;
                    break;
                }
                else
                    throw invalid_argument("Invalid year");
            }
            catch (...)
            {
                cout << "║ ❌ Invalid year. Please enter a valid year: ";
            }
        }

        // ویرایش تعداد دروس
        cout << "║ Enter Number of Courses (current: " << s.courses.size() << "): ";
        while (true)
        {
            getline(cin, input);
            if (input.empty())
                break;
            try
            {
                int count = stoi(input);
                if (count >= 0)
                {
                    s.courses.resize(count);
                    for (int i = 0; i < count; ++i)
                    {
                        cout << "╠════════════════════════════════════════════════ Course " << i + 1 << " Details ══╣\n";

                        cout << "║ Course " << i + 1 << " Name (current: " << s.courses[i].name << "): ";
                        getline(cin, input);
                        if (!input.empty())
                            s.courses[i].name = input;

                        cout << "║ Course Weight (current: " << s.courses[i].weight << "): ";
                        while (true)
                        {
                            getline(cin, input);
                            if (input.empty())
                                break;
                            try
                            {
                                int weight = stoi(input);
                                if (weight >= 1 && weight <= 3)
                                {
                                    s.courses[i].weight = weight;
                                    break;
                                }
                                else
                                    throw invalid_argument("Invalid weight");
                            }
                            catch (...)
                            {
                                cout << "║ ❌ Invalid weight. Please enter a value between 1 and 3: ";
                            }
                        }

                        cout << "║ Course Grade (current: " << s.courses[i].grade << "): ";
                        while (true)
                        {
                            getline(cin, input);
                            if (input.empty())
                                break;
                            try
                            {
                                double grade = stod(input);
                                if (grade >= 0.0 && grade <= 100.0)
                                {
                                    s.courses[i].grade = grade;
                                    break;
                                }
                                else
                                    throw invalid_argument("Invalid grade");
                            }
                            catch (...)
                            {
                                cout << "║ ❌ Invalid grade. Please enter a value between 0 and 100: ";
                            }
                        }
                    }
                    break;
                }
                else
                    throw invalid_argument("Invalid count");
            }
            catch (...)
            {
                cout << "║ ❌ Invalid count. Please enter a non-negative integer: ";
            }
        }

        // نمایش پیام موفقیت
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ✅ Student updated successfully!                                    ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }
    else
    {
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Operation canceled. The student was not deleted.                 ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }

    cout << "═══════════════════════════════════════════════════════════════════════\n";
    waitForKeyPress();
}

// حذف دانش‌آموز
void Manager::deleteStudent()
{
    cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           🗑️  Delete Student                         ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ Enter Student ID to Delete: ";

    int id;
    // بررسی ورودی صحیح
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a valid integer for Student ID: ";
    }

    // پیدا کردن دانش‌آموز
    auto it = find_if(students.begin(), students.end(), [id](const Student &s)
                      { return s.id == id; });

    if (it != students.end())
    {
        const Student &student = *it;
        // نمایش اطلاعات دانش‌آموز
        cout << "╠═══════════════════════════════════════════════════════ informaion ══╣\n";
        cout << "║ - ID: " << student.id << "                                          \n";
        cout << "║ - Name: " << student.firstName << " " << student.lastName << "       \n";
        cout << "║ - Entry Year: " << student.entryYear << "                          \n";
        cout << "║ - Avg Grade: " << fixed << setprecision(2) << student.averageGrade() << "\n";
        cout << "╠═════════════════════════════════════════════════════════════════════╣\n";

        // گرفتن تأیید
        char confirm;
        cout << "║ Are you sure you want to delete this student? (y/n): ";
        cin >> confirm;

        if (tolower(confirm) == 'y')
        {
            // حذف دانش‌آموز
            students.erase(it);

            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            // نمایش پیام موفقیت
            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ✅ Student deleted successfully!                                    ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }
        else
        {
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ❌ Operation canceled. The student was not deleted.                 ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }
    }
    else
    {
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "\n⚠️ No student found with ID " << id << "!\n";
    }

    cout << "═══════════════════════════════════════════════════════════════════════\n";
    waitForKeyPress();
}

void Manager::filterStudents()
{
    int choice;
    do
    {
        clearConsole();
        cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                        🔍 Filter Students                           ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "╔═══════════════════════════════════════ 📋 Select Filter Criterion ══╗\n";
        cout << "║ 1️⃣  Entry Year                                                       ║\n";
        cout << "║ 2️⃣  Course Name                                                      ║\n";
        cout << "║ 3️⃣  Grade Above Threshold                                            ║\n";
        cout << "║ 0️⃣  Back to Main Menu                                                ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ Your Choice: ";

        while (!(cin >> choice) || choice < 0 || choice > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "║ ❌ Invalid choice. Enter a number between ( 0 and 3 ): ";
        }

        if (choice == 0)
        {
            cout << "╚═════════════════════════════════════════════ Return to Table Menu ══╝\n";
            waitForKeyPress();
            break;
        }

        vector<Student> filteredStudents;

        switch (choice)
        {
        case 1:
        {
            int year;
            cout << "║ Enter Entry Year to filter (e.g., 1400): ";
            while (!(cin >> year))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "║ ❌ Invalid input. Enter a valid year: ";
            }

            for (const auto &student : students)
            {
                if (student.entryYear == year)
                    filteredStudents.push_back(student);
            }
            break;
        }
        case 2:
        {
            string courseName;
            cout << "║ Enter Course Name to filter: ";
            cin.ignore();
            getline(cin, courseName);

            for (const auto &student : students)
            {
                for (const auto &course : student.courses)
                {
                    if (caseInsensitiveCompare(courseName, course.name))
                    {
                        filteredStudents.push_back(student);
                        break;
                    }
                }
            }
            break;
        }
        case 3:
        {
            double gradeThreshold;
            cout << "║ Enter Grade Threshold (e.g., 75): ";
            while (!(cin >> gradeThreshold) || gradeThreshold < 0.0 || gradeThreshold > 100.0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "║ ❌ Invalid input. Enter a grade between 0 and 100: ";
            }

            for (const auto &student : students)
            {
                for (const auto &course : student.courses)
                {
                    if (course.grade > gradeThreshold)
                    {
                        filteredStudents.push_back(student);
                        break;
                    }
                }
            }
            break;
        }
        }

        // نمایش دانش‌آموزان فیلتر شده
        if (filteredStudents.empty())
        {
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ❌ No students found matching the criteria.                         ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }
        else
        {
            cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║                     Filtered Students List                          ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            for (const auto &student : filteredStudents)
            {
                cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
                cout << "║ ID: " << student.id << "\n";
                cout << "║ Name: " << student.firstName << " " << student.lastName << "\n";
                cout << "║ Entry Year: " << student.entryYear << "\n";
                cout << "║ Courses:\n";

                for (const auto &course : student.courses)
                {
                    cout << "║   - " << course.name << " (Weight: " << course.weight
                         << ", Grade: " << course.grade << ")\n";
                }
                cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
            }
        }

        cout << "═══════════════════════════════════════════════════════════════════════\n";
        waitForKeyPress();
    } while (choice != 0);
}

void Manager::saveStudentsToFileSorted() const
{
    // مرتب‌سازی دانش‌آموزان بر اساس ID
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(), [](const Student &a, const Student &b)
         { return a.id < b.id; });

    // ذخیره اطلاعات دانش‌آموزان در فایل JSON
    json jArray;
    for (const auto &s : sortedStudents)
    {
        jArray.push_back(s.toJSON());
    }

    ofstream outFile(studentFilename);
    if (outFile.is_open())
    {
        outFile << jArray.dump(2); // ذخیره JSON با فرمت زیبا
        outFile.close();
    }
    else
    {
        cout << "\n║ ❌ Error: Unable to open file for saving.\n";
    }
}

// بارگذاری دانش‌آموزان از فایل JSON
void Manager::loadStudentsFromFile()
{
    ifstream inFile(studentFilename);
    if (inFile.is_open())
    {
        json jArray;
        inFile >> jArray;
        students.clear();
        for (const auto &j : jArray)
        {
            students.push_back(Student::fromJSON(j));
        }
        inFile.close();
    }
    else
    {
        return;
    }
}

void Manager::exportToExcel(const string &outputFilename) const
{
    ofstream outFile(outputFilename);
    if (!outFile.is_open())
    {
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        // نمایش پیام موفقیت
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Error: Unable to open file for writing.                          ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        return;
    }

    // نوشتن هدر فایل CSV
    outFile << "ID,First Name,Last Name,Entry Year,Course Name,Course Weight,Course Grade\n";

    // نوشتن اطلاعات دانش‌آموزان
    for (const auto &student : students)
    {
        for (const auto &course : student.courses)
        {
            outFile << student.id << ","
                    << student.firstName << ","
                    << student.lastName << ","
                    << student.entryYear << ","
                    << course.name << ","
                    << course.weight << ","
                    << fixed << setprecision(2) << course.grade << "\n";
        }

        // در صورت نداشتن درس، فقط اطلاعات دانش‌آموز چاپ می‌شود
        if (student.courses.empty())
        {
            outFile << student.id << ","
                    << student.firstName << ","
                    << student.lastName << ","
                    << student.entryYear << ","
                    << "No Courses,"
                    << "0,"
                    << "0.00\n";
        }
    }

    outFile.close();
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    // نمایش پیام موفقیت
    cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ ✅ Data exported successfully to " << outputFilename << "!              ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    cout << "═══════════════════════════════════════════════════════════════════════\n";
}

void Manager::run()
{
    accessMenu();
}

void Manager::studentLogin()
{
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    int studentId;

    cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           Student Login                             ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝";

    cout << "\n╔═════════════════════════════════════════════════════════════════════╗";
    cout << "\n║ Enter your Student ID: ";
    cin >> studentId;

    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    bool found = false;
    for (auto &student : students) // students آرایه‌ای از اطلاعات دانش‌آموزان
    {
        if (student.id == studentId)
        {
            found = true;

            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ✅ Welcome " << student.firstName + ' ' + student.lastName << " You have successfully logged in.\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "═══════════════════════════════════════════════════════════════════════\n";
            waitForKeyPress();

            studentMenu(student);
        }
    }

    if (!found)
    {
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Student Code not found. Please try again.                        ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "═══════════════════════════════════════════════════════════════════════\n";
        waitForKeyPress();
    }
}

void Manager::teacherLogin()
{
    cout << "\n\033[1;34m╔═════════════════════════════════════════════════════════════════════╗\033[0m\n";
    cout << "\033[1;34m║\033[0m                   \033[1;33mWelcome to Teacher Login Panel\033[0m                    \033[1;34m║\033[0m\n";
    cout << "\033[1;34m╚═════════════════════════════════════════════════════════════════════╝\033[0m\n";

    string id, password;
    cout << "\033[1;32mEnter your ID: \033[0m";
    cin >> id;
    cout << "\033[1;32mEnter your Password: \033[0m";
    cin >> password;

    // جستجوی استاد
    auto it = std::find_if(teachers.begin(), teachers.end(), [&](const Teacher &teacher)
                           { return teacher.id == id; });

    if (it != teachers.end())
    {
        // بررسی صحت رمز عبور
        if (it->password == password)
        {
            clearConsole();
            cout << "\n\033[1;34m╔═════════════════════════════════════════════════════════════════════╗\033[0m\n";
            cout << "\033[1;34m║\033[0m            \033[1;32mWelcome, " << it->firstName + " " + it->lastName << "!\033[0m                   \033[1;34m║\033[0m\n";
            cout << "\033[1;34m╚═════════════════════════════════════════════════════════════════════╝\033[0m\n";

            teacherMenu(*it); // فراخوانی منوی اختصاصی معلم
        }
        else
        {
            cout << "\033[1;31m❌ Incorrect Password. Please try again.\033[0m\n";
            waitForKeyPress();
        }
    }
    else
    {
        cout << "\033[1;31m❌ National ID not found. Please try again.\033[0m\n";
        waitForKeyPress();
    }
}

void Manager::manageTeachers()
{
    while (true)
    {
        loadStudentsFromFile();

        // هدر لیست دانش‌آموزان
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                    📝 Teachers List                                      ║\n";
        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // ستون‌های جدول
        cout << "║ " << left << setw(14) << "🔢 ID"
             << setw(25) << "👤 First Name"
             << setw(22) << "👥 Last Name"
             << setw(12) << "📅 Year"
             << setw(17) << "📊 Avg Grade"
             << setw(8) << "Weights" << " ║\n";

        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // اطلاعات دانش‌آموزان
        for (const auto &s : students)
        {
            cout << "║ " << left << setw(13) << s.id
                 << setw(23) << s.firstName
                 << setw(20) << s.lastName
                 << setw(13) << s.entryYear
                 << setw(15) << fixed << setprecision(2) << s.averageGrade()
                 << setw(4) << s.totalWeight() << " ║\n";
        }

        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n";

        // منوی انتخاب گزینه‌ها
        cout << "\n╔═══════════════════════════════════════════════════════ 📋 Options ══╗\n";
        cout << "║ 1️⃣  Add a Teacher                                                    ║\n";
        cout << "║ 2️⃣  Edit a Teacher                                                   ║\n";
        cout << "║ 3️⃣  Delete a Teacher                                                 ║\n";
        cout << "║ 4️⃣  View Teacher Details                                             ║\n";
        cout << "║ 0️⃣  Return to Main Menu                                              ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        int option;
        cout << "╔" << "═════════════════════════════════════════════════════════════════════" << "╗";
        cout << "\n║ Your Choice: ";
        while (!(cin >> option) || option < 0 || option > 4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "║ ❌ Invalid choice. Enter a number between ( 0 and 5 ): ";
        }

        if (option != 0)
        {
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }

        switch (option)
        {
        case 1:
            clearConsole();
            addTeacher();
            saveTeachersToFileSorted();
            break;
        case 2:
            editStudent();
            saveTeachersToFileSorted();
            break;
        case 3:
            deleteStudent();
            saveTeachersToFileSorted();
            break;
        case 4:
            showStudentDetails();
            break;
        case 0:
            cout << "╚═════════════════════════════════════════════ Return to Admin Menu ══╝\n";

            waitForKeyPress();
            return;
        default:
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ❌ Invalid choice. Please try again.                                ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "═══════════════════════════════════════════════════════════════════════\n";
            waitForKeyPress();
            break;
        }
    }
}

void Manager::addTeacher()
{
    Teacher teacher;

    clearConsole();

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           📋 Add Teacher                            ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";

    while (true)
    {
        cout << "║ Enter Teacher ID: ";
        cin >> teacher.id;

        bool idExists = false;
        for (const auto &t : teachers)
        {
            if (t.id == teacher.id)
            {
                idExists = true;
                break;
            }
        }

        if (idExists)
        {
            cout << "║ ❌ A teacher with this ID already exists! Please try again.\n";
        }
        else
        {
            break;
        }
    }

    cin.ignore();
    cout << "║ Enter First Name: ";
    getline(cin, teacher.firstName);

    cout << "║ Enter Last Name: ";
    getline(cin, teacher.lastName);

    cout << "║ Enter Password: ";
    getline(cin, teacher.password);

    // وارد کردن تاریخ تولد
    int birthYear, birthMonth, birthDay;
    while (true)
    {
        cout << "║ Enter Birth Year (e.g., 1365): ";
        cin >> birthYear;
        cout << "║ Enter Birth Month (1-12): ";
        cin >> birthMonth;
        cout << "║ Enter Birth Day (1-31): ";
        cin >> birthDay;

        if (isValidDate(birthYear, birthMonth, birthDay))
        {
            teacher.birthYear = birthYear;
            teacher.birthMonth = birthMonth;
            teacher.birthDay = birthDay;
            break;
        }
        else
        {
            cout << "║ ❌ Invalid date. Please enter a valid date in the Persian calendar.║\n";
        }
    }

    // وارد کردن تعداد دروس
    int courseCount;
    cout << "║ Enter the number of courses to assign: ";
    while (!(cin >> courseCount) || courseCount < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a non-negative integer: ";
    }

    cin.ignore();
    for (int i = 0; i < courseCount; ++i)
    {
        string courseName;
        cout << "║ Enter Course Name #" << (i + 1) << ": ";
        getline(cin, courseName);
        teacher.courses.push_back(courseName);
    }

    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    teachers.push_back(teacher);

    const int currentYear = 1402;
    int age = currentYear - teacher.birthYear;

    cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ ✅ Teacher added successfully!                                      ║\n";
    cout << "╠══════════════════════════════════════════════════════ Information ══╣\n";

    cout << "║ ID: " << teacher.id << "\n";
    cout << "║ Name: " << teacher.firstName << " " << teacher.lastName << "\n";
    cout << "║ Birth Date (Shamsi): " << teacher.birthYear << "/" << teacher.birthMonth << "/" << teacher.birthDay << "\n";
    cout << "║ Age: " << age << "\n";
    cout << "║ Number of Courses: " << teacher.courses.size() << "\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    waitForKeyPress();
}

void Manager::editTeacher()
{
    clearConsole();
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           ✏️ Edit Teacher                           ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "Enter Teacher ID to edit: ";
    string id;
    cin >> id;

    // پیدا کردن استاد با ID مشخص‌شده
    auto it = find_if(teachers.begin(), teachers.end(), [id](const Teacher &t)
                      { return t.id == id; });

    if (it != teachers.end())
    {
        Teacher &t = *it;

        string input;
        cin.ignore();

        cout << "Enter New First Name (current: " << t.firstName << "): ";
        getline(cin, input);
        if (!input.empty())
            t.firstName = input;

        cout << "Enter New Last Name (current: " << t.lastName << "): ";
        getline(cin, input);
        if (!input.empty())
            t.lastName = input;

        cout << "✅ Teacher updated successfully!\n";
    }
    else
    {
        cout << "❌ No teacher found with ID " << id << "!\n";
    }

    waitForKeyPress();
}

void Manager::deleteTeacher()
{
    clearConsole();
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           🗑️ Delete Teacher                        ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "Enter Teacher ID to delete: ";
    string id;
    cin >> id;

    auto it = find_if(teachers.begin(), teachers.end(), [id](const Teacher &t)
                      { return t.id == id; });

    if (it != teachers.end())
    {
        teachers.erase(it);
        cout << "✅ Teacher deleted successfully!\n";
    }
    else
    {
        cout << "❌ No teacher found with ID " << id << "!\n";
    }

    waitForKeyPress();
}

void Manager::listTeachers()
{
    waitForKeyPress();

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                          📋 List of Teachers                       ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    if (teachers.empty())
    {
        cout << "No teachers found!\n";
    }
    else
    {
        for (const auto &t : teachers)
        {
            cout << "ID: " << t.id << ", Name: " << t.firstName << " " << t.lastName
                 << "\n";
        }
    }

    waitForKeyPress();
}

void Manager::saveTeachersToFileSorted() const
{
    // مرتب کردن بر اساس nationalID
    vector<Teacher> sortedTeachers = teachers;
    sort(sortedTeachers.begin(), sortedTeachers.end(), [](const Teacher &a, const Teacher &b)
         { return a.id < b.id; });

    // تبدیل به JSON
    json jArray;
    for (const auto &teacher : sortedTeachers)
    {
        jArray.push_back(teacher.Teacher::toJSON());
    }

    // ذخیره در فایل
    ofstream file(teacherFilename);
    if (file.is_open())
    {
        file << jArray.dump(2); // ذخیره با فرمت زیبا
        file.close();
    }
    else
    {
        cerr << "║ ❌ Unable to open file " << teacherFilename << " for writing!\n";
    }
}

// بارگذاری دانش‌آموزان از فایل JSON
void Manager::loadTeachersFromFile()
{
    ifstream inFile(teacherFilename);
    if (inFile.is_open())
    {
        json jArray;
        inFile >> jArray;

        teachers.clear();
        for (const auto &j : jArray)
        {
            teachers.push_back(Teacher::fromJSON(j));
        }
        inFile.close();
    }
    else
    {
        return;
    }
}

void Manager::adminLogin()
{
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    const string adminUsername = "admin"; // نام کاربری پیش‌فرض
    const string adminPassword = "admin"; // رمز عبور پیش‌فرض

    string username, password;

    cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           🛡️  Admin Login                            ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔" << "═════════════════════════════════════════════════════════════════════" << "╗";
    cout << "\n║ Enter Username: ";
    cin >> username;
    cout << "║ Enter Password: ";
    cin >> password;

    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    if (username == adminUsername && password == adminPassword)
    {
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ✅ Welcome Admin! You have successfully logged in.                  ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "═══════════════════════════════════════════════════════════════════════\n";
        waitForKeyPress();

        adminMenu();
    }
    else
    {
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Invalid username or password. Please try again.                  ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "═══════════════════════════════════════════════════════════════════════\n";
        waitForKeyPress();
    }
}