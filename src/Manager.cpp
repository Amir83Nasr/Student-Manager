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

    string id;
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

            double totalWeight = 0.0, weightedGradeSum = 0.0;
            int totalCourses = student.courses.size();

            for (const auto &course : student.courses)
            {
                cout << "║ " << setw(24) << left << course.name
                     << setw(11) << left << course.weight
                     << setw(12) << left << fixed << setprecision(2) << course.grade << "                     ║\n";
                totalWeight += course.weight;
                weightedGradeSum += course.grade * course.weight;
            }

            double averageGrade = (totalWeight > 0) ? (weightedGradeSum / totalWeight) : 0.0;

            cout << "╠═════════════════════════════════════════════════════════════════════╣\n";
            cout << "║ " << setw(24) << left << "Summary"
                 << setw(11) << left << totalWeight
                 << setw(12) << left << fixed << setprecision(2) << averageGrade << "                     ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }
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

    string id;
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

    string id;
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
        cout << "║ - ID         : " << student.id << "\n";
        cout << "║ - Name       : " << student.firstName << " " << student.lastName << "\n";
        cout << "║ - Entry Year : " << student.entryYear << "\n";
        cout << "║ - Avg Grade  : " << fixed << setprecision(2) << student.averageGrade() << "\n";
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

    string studentId;

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
        cout << "║ ❌ Student id not found. Please try again.                        ║\n";
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
        loadTeachersFromFile();

        // هدر لیست اساتید
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                       Teacher List                                       ║\n";
        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // ستون‌های جدول
        cout << "║ " << left << setw(15) << "🔢 ID"
             << setw(25) << "👤 First Name"
             << setw(22) << "👥 Last Name"
             << setw(21) << "📅 Birth Date"
             << setw(15) << "📚 Courses" << " ║\n";

        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // اطلاعات اساتید
        for (const auto &t : teachers)
        {
            string birthDate = to_string(t.birthYear) + "/" + to_string(t.birthMonth) + "/" + to_string(t.birthDay);
            int age = calculateAge(t.birthYear);

            cout << "║ " << left << setw(13) << t.id
                 << setw(23) << t.firstName
                 << setw(20) << t.lastName
                 << setw(21) << birthDate
                 << setw(11) << t.courses.size() << " ║\n";
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
            editTeacher();
            saveTeachersToFileSorted();
            break;
        case 3:
            deleteTeacher();
            saveTeachersToFileSorted();
            break;
        case 4:
            showTeacherDetails();
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
    cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                             Edit Teacher                            ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ Enter Teacher ID to Edit: ";

    string id;
    // بررسی ورودی معتبر
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a valid integer for Teacher ID: ";
    }

    auto it = find_if(teachers.begin(), teachers.end(), [id](const Teacher &t)
                      { return t.id == id; });

    if (it != teachers.end())
    {
        clearConsole();
        Teacher &teacher = *it;

        string birthDate = to_string(teacher.birthYear) + "/" + to_string(teacher.birthMonth) + "/" + to_string(teacher.birthDay);
        int age = calculateAge(teacher.birthYear);

        cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                             Edit Teacher                            ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        cout << "╔══════════════════════════════════════════════════════ Information ══╗\n";
        cout << "║ - ID          : " << teacher.id << "                                                \n";
        cout << "║ - Name        : " << teacher.firstName << " " << teacher.lastName << "                  \n";
        cout << "║ - Birth Date  : " << birthDate << "                                 \n";
        cout << "║ - Age         : " << age << "                                       \n";
        cout << "╠═════════════════════════════════════════════════════════════════════╣\n";

        string input;
        cin.ignore();

        // ویرایش نام
        cout << "║ Enter New First Name (current: " << teacher.firstName << "): ";
        getline(cin, input);
        if (!input.empty())
            teacher.firstName = input;

        cout << "║ Enter New Last Name (current: " << teacher.lastName << "): ";
        getline(cin, input);
        if (!input.empty())
            teacher.lastName = input;

        // ویرایش سال ورود
        cout << "║ Enter New Birth Date " << " (current: " << birthDate << "): \n";
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

        // ویرایش تعداد دروس
        cout << "║ Enter Number of Courses (current: " << teacher.courses.size() << "): ";
        int numCourses;
        while (true)
        {
            if (cin >> numCourses && numCourses >= 0)
            {
                teacher.courses.resize(numCourses);
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "║ ❌ Invalid input. Enter a non-negative integer: ";
            }
        }

        cin.ignore(); // پاک کردن بافر برای دریافت نام دروس

        // ویرایش نام دروس
        for (int i = 0; i < numCourses; ++i)
        {
            cout << "║ Enter Name for Course " << i + 1 << " (current: " << teacher.courses[i] << "): ";
            getline(cin, input);
            if (!input.empty())
                teacher.courses[i] = input;
        }

        // پیام موفقیت
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ✅ Teacher updated successfully!                                    ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }
    else
    {
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Operation canceled. The teacher was not found.                   ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }

    cout << "═══════════════════════════════════════════════════════════════════════\n";
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

void Manager::showTeacherDetails()
{
    cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                      View Teacher Informations                      ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ Enter Teacher ID to View: ";

    string id;
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a valid integer for Teacher ID: ";
    }

    // پیدا کردن دانش‌آموز
    auto it = find_if(teachers.begin(), teachers.end(), [id](const Teacher &t)
                      { return t.id == id; });

    if (it != teachers.end())
    {
        clearConsole();
        const Teacher &teacher = *it;

        // هدر
        cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                          Teacher Details                            ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        string birthDate = to_string(teacher.birthYear) + "/" + to_string(teacher.birthMonth) + "/" + to_string(teacher.birthDay);
        int age = calculateAge(teacher.birthYear);

        // اطلاعات دانش‌آموز
        cout << "╔══════════════════════════════════════════════════════ Information ══╗\n";
        cout << "║ ID          : " << teacher.id << "\n";
        cout << "║ First Name  : " << teacher.firstName << "\n";
        cout << "║ Last Name   : " << teacher.lastName << "\n";
        cout << "║ Birth Date  : " << birthDate << "\n";
        cout << "║ Age         : " << age << "\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        if (teacher.courses.empty())
        {
            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ⚠️  No courses found for this teacher!                               ║\n";
        }
        else
        {
            // نمایش اطلاعات درس‌ها
            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║                           Courses Details                           ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ " << setw(24) << left << "Course Name" << setw(44) << left << "Weight" << "║\n";
            cout << "╠═════════════════════════════════════════════════════════════════════╣\n";

            for (const auto &course : teacher.courses)
            {
                cout << "║ " << setw(24) << left << course << "\n";
            }
        }

        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }
    else
    {
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Operation canceled. The Teacher was not deleted.                 ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        cout << "═══════════════════════════════════════════════════════════════════════\n";
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

void Manager::manageCourses()
{
    while (true)
    {
        loadCoursesFromFile();

        // هدر لیست اساتید
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                     Cources List                                         ║\n";
        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // ستون‌های جدول
        cout << "║ " << left << setw(15) << "🔢 id"
             << setw(27) << "👤 Course Name"
             << setw(20) << "📚 Weight"
             << setw(34) << "👥 Instructor" << " ║\n";

        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // اطلاعات اساتید
        for (const auto &c : courses)
        {
            cout << "║ " << left << setw(13) << c.id
                 << setw(30) << c.name
                 << setw(15) << c.weight
                 << setw(30) << c.instructor << " ║\n";
        }

        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n";

        // منوی انتخاب گزینه‌ها
        cout << "\n╔═══════════════════════════════════════════════════════ 📋 Options ══╗\n";
        cout << "║ 1️⃣  Add a Cource                                                     ║\n";
        cout << "║ 2️⃣  Edit a Cource                                                    ║\n";
        cout << "║ 3️⃣  Delete a Cource                                                  ║\n";
        cout << "║ 0️⃣  Return to Admin Menu                                             ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        int option;
        cout << "╔" << "═════════════════════════════════════════════════════════════════════" << "╗";
        cout << "\n║ Your Choice: ";
        while (!(cin >> option) || option < 0 || option > 3)
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
            addCourse();
            saveCoursesToFileSorted();
            break;
        case 2:
            editCourse();
            saveCoursesToFileSorted();
            break;
        case 3:
            deleteCourse();
            saveCoursesToFileSorted();
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

void Manager::saveCoursesToFileSorted() const
{
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course &a, const Course &b)
         { return a.id < b.id; });

    json jArray;
    for (const auto &course : sortedCourses)
    {
        jArray.push_back(course.toJSON());
    }

    ofstream outFile(courseFilename);
    if (outFile.is_open())
    {
        outFile << jArray.dump(2);
        outFile.close();
    }
    else
    {
        cout << "\n║ ❌ Error: Unable to open file for saving.\n";
    }
}

void Manager::loadCoursesFromFile()
{
    ifstream inFile(courseFilename);
    if (inFile.is_open())
    {
        json jArray;
        inFile >> jArray;
        courses.clear();
        for (const auto &j : jArray)
        {
            courses.push_back(Course::fromJSON(j));
        }
        inFile.close();
    }
    else
    {
        return;
    }
}

void Manager::addCourse()
{
    loadTeachersFromFile();

    if (teachers.empty())
    {
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ The teacher list is empty. Please add teachers first.            ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "═══════════════════════════════════════════════════════════════════════\n";
        waitForKeyPress();
        return;
    }

    Course newCourse;
    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           📋 Add Course                             ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═══════════════════════════════════════════════════════ informaion ══╗\n";

    // Input course id
    bool isUnique;
    do
    {
        cout << "║ Enter course id: ";
        cin >> newCourse.id;

        // Check if the id is unique
        isUnique = true;
        for (const auto &course : courses)
        {
            if (course.id == newCourse.id)
            {
                isUnique = false;
                break;
            }
        }

        if (!isUnique)
        {
            cout << "║ ❌ This course id already exists. Please enter a different id.\n";
        }
    } while (!isUnique);

    // Input course name
    cout << "║ Enter course name: ";
    cin.ignore();
    getline(cin, newCourse.name);

    // Input course weight (limited to 0, 1, 2, 3)
    do
    {
        cout << "║ Enter course weight (0, 1, 2, 3): ";
        cin >> newCourse.weight;

        if (newCourse.weight < 0 || newCourse.weight > 3)
        {
            cout << "║ ❌ Invalid weight. Please enter 0, 1, 2, or 3.\n";
        }
    } while (newCourse.weight < 0 || newCourse.weight > 3);

    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    // Display teacher list and choose instructor
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                  Available Teachers                                      ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

    // ستون‌های جدول
    cout << "║ " << left << setw(15) << "🔢 NO."
         << setw(25) << "👤 First Name"
         << setw(22) << "👥 Last Name"
         << setw(21) << "📅 Age"
         << setw(15) << "📚 Courses" << " ║\n";

    cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

    // Display teachers
    for (size_t i = 0; i < teachers.size(); ++i)
    {
        string birthDate = to_string(teachers[i].birthYear) + "/" + to_string(teachers[i].birthMonth) + "/" + to_string(teachers[i].birthDay);
        int age = calculateAge(teachers[i].birthYear);

        cout << "║ " << left << setw(13) << i + 1
             << setw(23) << teachers[i].firstName
             << setw(20) << teachers[i].lastName
             << setw(21) << age
             << setw(11) << teachers[i].courses.size() << " ║\n";
    }
    cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

    int instructorIndex = 0;
    do
    {
        cout << "║ Select an instructor by number: ";
        cin >> instructorIndex;

        if (instructorIndex < 1 || instructorIndex > teachers.size())
        {
            cout << "║ ❌ Invalid selection. Please try again.\n";
        }
    } while (instructorIndex < 1 || instructorIndex > teachers.size());

    newCourse.instructor = teachers[instructorIndex - 1].firstName + " " + teachers[instructorIndex - 1].lastName;

    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n";

    // Confirm details with admin
    char confirm;
    cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║             📝 Review the course details before saving              ║\n";
    cout << "╠═════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ - Course id   : " << newCourse.id << "\n";
    cout << "║ - Course Name : " << newCourse.name << "\n";
    cout << "║ - Instructor  : " << newCourse.instructor << "\n";
    cout << "║ - Weight      : " << newCourse.weight << "\n";
    cout << "╠═════════════════════════════════════════════════════════════════════╣\n";

    cout << "║ Do you confirm these details? (y/n): ";
    cin >> confirm;

    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    if (tolower(confirm) == 'n')
    {
        cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ The course addition process was canceled.                        ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "═══════════════════════════════════════════════════════════════════════\n";
        waitForKeyPress();

        return;
    }

    // Add course to the list
    courses.push_back(newCourse);

    cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ ✅ Course added successfully!                                       ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "═══════════════════════════════════════════════════════════════════════\n";
    waitForKeyPress();
}

void Manager::deleteCourse()
{
    cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                          🗑️  Delete Courese                          ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ Enter Course ID to Delete: ";

    string id;
    // بررسی ورودی صحیح
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "║ ❌ Invalid input. Enter a valid integer for Course ID: ";
    }

    auto it = find_if(courses.begin(), courses.end(), [id](const Course &c)
                      { return c.id == id; });

    if (it != courses.end())
    {
        const Course &course = *it;

        cout << "╠═══════════════════════════════════════════════════════ informaion ══╣\n";
        cout << "║ - ID          : " << course.id << "\n";
        cout << "║ - Course Name : " << course.name << "\n";
        cout << "║ - Weight      : " << course.weight << "\n";
        cout << "║ - Instructor  : " << course.instructor << "\n";
        cout << "╠═════════════════════════════════════════════════════════════════════╣\n";

        // گرفتن تأیید
        char confirm;
        cout << "║ Are you sure you want to delete this course? (y/n): ";
        cin >> confirm;

        if (tolower(confirm) == 'y')
        {
            // حذف دانش‌آموز
            courses.erase(it);

            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            // نمایش پیام موفقیت
            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ✅ Course deleted successfully!                                     ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }
        else
        {
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

            cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ❌ Operation canceled. The course was not deleted.                  ║\n";
            cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        }
    }
    else
    {
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "\n⚠️ No course found with ID " << id << "!\n";
    }

    cout << "═══════════════════════════════════════════════════════════════════════\n";
    waitForKeyPress();
}

void Manager::editCourse()
{
    if (courses.empty())
    {
        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ No courses available to edit.                                    ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
        waitForKeyPress();
        return;
    }

    cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                             Edit Course                             ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

    cout << "╔═════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ Enter Course ID to Edit: ";
    string id;
    cin >> id;

    auto it = find_if(courses.begin(), courses.end(), [&id](const Course &c)
                      { return c.id == id; });

    if (it != courses.end())
    {
        clearConsole();
        Course &course = *it;

        cout << "\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                             Edit Course                             ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        cout << "╔═══════════════════════════════════════════════════════ informaion ══╗\n";
        cout << "║ - Course ID   : " << course.id << "\n";
        cout << "║ - Course Name : " << course.name << "\n";
        cout << "║ - Weight      : " << course.weight << "\n";
        cout << "║ - Instructor  : " << course.instructor << "\n";
        cout << "╠═════════════════════════════════════════════════════════════════════╣\n";

        string input;
        cin.ignore();

        // Edit course name
        cout << "║ Enter Course Name (current: " << course.name << "): ";
        getline(cin, input);
        if (!input.empty())
            course.name = input;

        // Edit course weight
        int newWeight = -1;
        do
        {
            cout << "║ Enter Course Weight (0, 1, 2, 3), (current: " << course.weight << "): ";
            getline(cin, input);
            if (input.empty())
                break;
            try
            {
                newWeight = stoi(input);
                if (newWeight >= 0 && newWeight <= 3)
                {
                    course.weight = newWeight;
                    break;
                }
                else
                {
                    cout << "║ ❌ Invalid weight. Please enter a value between 0 and 3.\n";
                }
            }
            catch (...)
            {
                cout << "║ ❌ Invalid input. Please enter a number.\n";
            }
        } while (true);

        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";

        // Display teacher list and choose instructor
        cout << "\n╔══════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                  Available Teachers                                      ║\n";
        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // ستون‌های جدول
        cout << "║ " << left << setw(15) << "🔢 NO."
             << setw(25) << "👤 First Name"
             << setw(22) << "👥 Last Name"
             << setw(21) << "📅 Age"
             << setw(15) << "📚 Courses" << " ║\n";

        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        // Display teachers
        for (size_t i = 0; i < teachers.size(); ++i)
        {
            string birthDate = to_string(teachers[i].birthYear) + "/" + to_string(teachers[i].birthMonth) + "/" + to_string(teachers[i].birthDay);
            int age = calculateAge(teachers[i].birthYear);

            cout << "║ " << left << setw(13) << i + 1
                 << setw(23) << teachers[i].firstName
                 << setw(20) << teachers[i].lastName
                 << setw(21) << age
                 << setw(11) << teachers[i].courses.size() << " ║\n";
        }
        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n";

        int instructorIndex = 0;
        do
        {
            cout << "║ Select a New Instructor by Number (Press Enter to keep current: " << course.instructor << "): ";
            getline(cin, input);
            if (input.empty())
                break;

            try
            {
                instructorIndex = stoi(input);
                if (instructorIndex >= 1 && instructorIndex <= teachers.size())
                {
                    course.instructor = teachers[instructorIndex - 1].firstName + " " + teachers[instructorIndex - 1].lastName;
                    break;
                }
                else
                {
                    cout << "║ ❌ Invalid selection. Please select a valid number.\n";
                }
            }
            catch (...)
            {
                cout << "║ ❌ Invalid input. Please enter a number.\n";
            }
        } while (true);

        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n";

        cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ✅ Course updated successfully!                                     ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }
    else
    {
        cout << "\n\n╔═════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ❌ Course not found. Operation canceled.                            ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════╝\n";
    }

    cout << "═══════════════════════════════════════════════════════════════════════\n";
    waitForKeyPress();
}
