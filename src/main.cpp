#include "../include/Manager.h"
#include "../include/Utils.h"

// ———————————–––––––––––––––––(Main)---------------------------------

int main()
{
    clearConsole();
    Manager manager("../data/teachers.json", "../data/students.json", "../data/cources.json");
    manager.run();
    return 0;
}

// ————————————–––––––––––––––----------------------------------------