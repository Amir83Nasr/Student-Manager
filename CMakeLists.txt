cmake_minimum_required(VERSION 3.10)

# نام پروژه
project(StudentManager)

# تنظیم استاندارد زبان C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# افزودن فایل‌های منبع
set(SOURCES
    src/main.cpp
    src/Manager.cpp
    src/Student.cpp
    # src/Teacher.cpp
    src/Course.cpp
    src/Menu.cpp
    src/Utils.cpp
)

# افزودن فایل‌های هدر
set(HEADERS
    include/Manager.h
    include/Student.h
    # include/Teacher.h
    include/Course.h
    include/Utils.h
)

# افزودن کتابخانه nlohmann/json
include_directories(${CMAKE_SOURCE_DIR}/external/nlohmann_json/include)

# ایجاد فایل اجرایی
add_executable(StudentManager.exe ${SOURCES})

# افزودن مسیر هدرها
target_include_directories(StudentManager.exe PRIVATE include)
