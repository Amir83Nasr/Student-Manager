#include "../include/Utils.h"

// ———————————–––––––––––––––(Function)-------------------------------

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ——————————–––––––––––---------------------

void waitForKeyPress()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    clearConsole();
}

// ——————————–––––––––––---------------------

int getValidatedInt(const string &prompt, int min, int max)
{
    int value;
    cout << prompt;
    while (!(cin >> value) || value < min || value > max)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt;
    }
    cin.ignore();
    return value;
}

// ——————————–––––––––––---------------------

int currentYear()
{
    time_t t = time(nullptr);             // Get current time
    tm *timePtr = localtime(&t);          // Convert to local time structure
    return 1900 + timePtr->tm_year - 622; // Extract year (tm_year is years since 1900)
}

// ——————————–––––––––––---------------------

bool caseInsensitiveCompare(const std::string &str1, const std::string &str2)
{
    if (str1.size() != str2.size())
    {
        return false; // اگر طول رشته‌ها متفاوت باشد، برابر نیستند
    }

    return std::equal(str1.begin(), str1.end(), str2.begin(), [](unsigned char c1, unsigned char c2)
                      { return std::tolower(c1) == std::tolower(c2); });
}

// ——————————–––––––––––---------------------

int calculateAge(int birthYear)
{
    time_t t = time(nullptr);
    tm *currentTime = localtime(&t);

    int currentYear = currentTime->tm_year + 1900; // سال میلادی فعلی
    int shamsiYear = currentYear - 621;            // تبدیل به شمسی
    return shamsiYear - birthYear;
}

// ——————————–––––––––––---------------------

// void drawLine(char symbol = '═', int width = 70)
// {
//     cout << "╔" << string(width, symbol) << "╗\n";
// }

// ——————————–––––––––––---------------------

bool isValidDate(int year, int month, int day)
{
    if (year < 1300 || year > 1400)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    const int daysInMonth[] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
    return day <= daysInMonth[month - 1];
}

// ————————————–––––––––––––––----------------------------------------