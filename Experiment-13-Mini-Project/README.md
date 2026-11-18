# Student Portal

Menu-driven console mini project to add, list and search student records.

## Concepts
- Encapsulation with private data and public member functions
- STL map indexed by roll number
- CSV-style file persistence
- Input validation and exception handling

## Build
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o student_portal
./student_portal
```

Records are stored in `portal_students.csv` in the current working directory.
