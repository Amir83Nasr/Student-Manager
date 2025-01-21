#include "../include/Manager.h"
#include "../include/Student.h"
// #include "../include/Teacher.h"
#include "../include/Course.h"
#include "../include/Utils.h"

// ———————————–––––––––––––––(Manager)------------------------

Manager::Manager(const string &teacherFile, const string &studentFile) : teacherFilename(teacherFile), studentFilename(studentFile) {}

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

void Manager::listStudents()
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
    cout << "\n╔═════════════════════════════════════════════════════════════════════╗";
    cout << "\n║ Enter your Student ID: ";
    cin >> studentId;

    // جستجوی دانش‌آموز در لیست دانش‌آموزان
    bool found = false;
    for (auto &student : students) // students آرایه‌ای از اطلاعات دانش‌آموزان
    {
        if (student.id == studentId)
        {
            found = true;
            clearConsole();
            cout << "Welcome, " << student.firstName + ' ' + student.lastName << "!\n";
            studentMenu(student); // فراخوانی منوی اختصاصی دانش‌آموز
            break;
        }
    }

    if (!found)
    {
        cout << "❌ Student Code not found. Please try again.\n";
        waitForKeyPress();
    }
}