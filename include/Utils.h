#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>
#include <climits>
#include <ctime>
#include <string>
#include <algorithm>
#include <cctype>
#include <thread>

#include "../external/nlohmann_json/include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// ———————————–––––––––––––––(Function)-------------------------------

void clearConsole();
void waitForKeyPress();
// void drawLine(char symbol = '═', int width = 70);

int getValidatedInt(const string &prompt, int min = INT_MIN, int max = INT_MAX);
bool caseInsensitiveCompare(const string &str1, const string &str2);

int currentYear();
int calculateAge(int birthYear);
bool isValidDate(int year, int month, int day);

// ————————————–––––––––––––––----------------------------------------

#endif // UTILS_H
