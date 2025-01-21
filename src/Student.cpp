#include "../include/Student.h"
#include "../include/Course.h"

// ———————————–––––––––––––––---(Student)----------------------------

json Student::toJSON() const
{
    json courseArray = json::array();
    for (const auto &course : courses)
    {
        courseArray.push_back(course.toJSON());
    }

    return {
        {"id", id},
        {"firstName", firstName},
        {"lastName", lastName},
        {"entryYear", entryYear},
        {"courses", courseArray}};
}

// ——————————–––––––––––---------------------

Student Student::fromJSON(const json &j)
{
    Student s = {
        j.at("id").get<int>(),
        j.at("firstName").get<string>(),
        j.at("lastName").get<string>(),
        j.at("entryYear").get<int>(),
        {}};

    if (j.contains("courses") && j.at("courses").is_array())
    {
        for (const auto &courseJSON : j.at("courses"))
        {
            s.courses.push_back(Course::fromJSON(courseJSON));
        }
    }
    else
    {
        cout << "\n\u26A0\uFE0F Warning: Student with ID " << s.id << " has no courses.\n";
    }

    return s;
}

// ——————————–––––––––––---------------------

double Student::averageGrade() const
{
    double weightedSum = 0.0;
    int totalWeights = 0;

    for (const auto &course : courses)
    {
        weightedSum += course.grade * course.weight;
        totalWeights += course.weight;
    }

    return totalWeights > 0 ? weightedSum / totalWeights : 0.0;
}

// ——————————–––––––––––---------------------

int Student::totalWeight() const
{
    int total = 0;
    for (const auto &course : courses)
    {
        total += course.weight;
    }
    return total;
}

// ————————————–––––––––––––––----------------------------------------