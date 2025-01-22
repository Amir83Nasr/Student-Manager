#include "../include/Course.h"

// ———————————–––––––––––––––---(Course)----------------------------

json Course::toJSON() const
{
    return {
        {"id", id},
        {"name", name},
        {"instructor", instructor},
        {"weight", weight},
        {"grade", grade}};
}

// ——————————–––––––––––---------------------

Course Course::fromJSON(const json &j)
{
    Course cource;

    cource.id = j.at("id").get<string>();
    cource.name = j.at("name").get<string>();
    cource.instructor = j.at("instructor").get<string>();
    cource.weight = j.at("weight").get<int>();
    cource.grade = j.at("grade").get<double>();

    return cource;
}

// ————————————–––––––––––––––----------------------------------------