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

// ————————————–––––––––––––––----------------------------------------