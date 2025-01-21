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

#include "../external/nlohmann_json/include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// ———————————–––––––––––––––(Function)-------------------------------

void clearConsole();
void waitForKeyPress();
int getValidatedInt(const string &prompt, int min = INT_MIN, int max = INT_MAX);
int currentYear();
bool caseInsensitiveCompare(const std::string &str1, const std::string &str2);

// ————————————–––––––––––––––----------------------------------------

#endif // UTILS_H
