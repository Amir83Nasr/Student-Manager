# University Management System

Welcome to the **University Management System** project! This is a robust C++ application designed to efficiently manage university operations with a focus on three key roles: **Admin**, **Teacher**, and **Student**.

---

## Features

### Admin Features:
- Add, update, and delete teachers and students.
- Assign courses to teachers and students.
- View detailed information about all users.

### Teacher Features:
- Authenticate using unique credentials.
- Add and view courses.
- Manage students' grades.

### Student Features:
- View personal information and enrolled courses.
- Access grades and calculate weighted averages.

---

## Installation

### Prerequisites:
- **C++ Compiler**: GCC, Clang, or MSVC.
- **CMake**: For build automation.
- **SQLite3**: For database management.
- **Git** (optional): To clone the repository.

### Steps:

1. Clone the Repository:
   ```bash
   git clone https://github.com/your-repo/university-management-system.git
   cd university-management-system
   ```

2. Configure the Project:
   ```bash
   cmake -S . -B build
   ```

3. Build the Project:
   ```bash
   cmake --build build
   ```

4. Run the Application:
   ```bash
   ./build/university_management
   ```

---

## File Structure

```
📂 university-management-system
├── 📂 src
│   ├── main.cpp           # Entry point
│   ├── Manager.cpp        # Admin functionalities
│   ├── Teacher.cpp        # Teacher functionalities
│   ├── Student.cpp        # Student functionalities
│   └── ...
├── 📂 include
│   ├── Manager.h          # Admin header
│   ├── Teacher.h          # Teacher header
│   ├── Student.h          # Student header
│   └── ...
├── 📂 data
│   ├── students.json      # Student data
│   ├── teachers.json      # Teacher data
│   └── ...
├── CMakeLists.txt         # Build configuration
├── README.md              # Project documentation
└── .gitignore             # Git ignore rules
```

---

## Usage

### Admin Login:
- Default credentials:
  - **Username**: `admin`
  - **Password**: `admin`

### Teacher/Student Login:
- Use the credentials assigned during user creation.

---

## Screenshots

### Admin Dashboard:
![Admin Dashboard](https://via.placeholder.com/800x400.png?text=Admin+Dashboard)

### Teacher Course Management:
![Teacher Course Management](https://via.placeholder.com/800x400.png?text=Teacher+Course+Management)

### Student View:
![Student View](https://via.placeholder.com/800x400.png?text=Student+View)

---

## Contributing

We welcome contributions! Please follow these steps:

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your message here"
   ```
4. Push to the branch:
   ```bash
   git push origin feature-name
   ```
5. Submit a pull request.

---

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

## Contact

For any queries or support, please contact:

- **Email**: ah12.nasrollahi@gmail.com
- **GitHub**: [Amir83Nasr](https://github.com/Amir83Nasr)

---

Thank you for using the University Management System!

