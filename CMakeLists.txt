cmake_minimum_required(VERSION 3.10)

# نام پروژه
project(UniversityManagementSystem)

# تنظیم استاندارد زبان C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# افزودن فایل‌های منبع
set(SOURCES
    src/main.cpp
    src/Manager.cpp
    src/Student.cpp
    src/Teacher.cpp
    src/Course.cpp
    src/Menu.cpp
    src/Utils.cpp
)

# افزودن فایل‌های هدر
set(HEADERS
    include/Manager.h
    include/Student.h
    include/Teacher.h
    include/Course.h
    include/Utils.h
)

# تنظیم مسیر vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# پیدا کردن کتابخانه nlohmann-json
find_package(nlohmann_json CONFIG REQUIRED)

# ایجاد فایل اجرایی
add_executable(UniversityManagementSystem ${SOURCES})

# افزودن مسیر هدرها
target_include_directories(UniversityManagementSystem PRIVATE include)

# لینک کردن کتابخانه به پروژه
target_link_libraries(UniversityManagementSystem PRIVATE nlohmann_json::nlohmann_json)