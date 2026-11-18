#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct Student { int roll; string name; double marks; };

int main() {
    vector<Student> students{{3,"Riya",86.5},{1,"Arjun",72.0},
                             {2,"Kabir",91.0},{4,"Sara",64.5}};
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) { return a.marks > b.marks; });

    map<int,string> rollToName;
    unordered_map<string,double> nameToMarks;
    for (const auto& s : students) {
        rollToName[s.roll] = s.name;
        nameToMarks[s.name] = s.marks;
    }

    cout << "Sorted students:\\n";
    for (const auto& s : students)
        cout << s.roll << ' ' << s.name << ' ' << s.marks << '\\n';

    auto high = find_if(students.begin(), students.end(),
                        [](const Student& s) { return s.marks >= 80; });
    if (high != students.end()) cout << "First high scorer: " << high->name << '\\n';

    vector<double> marks(students.size());
    transform(students.begin(), students.end(), marks.begin(),
              [](const Student& s) { return s.marks; });
    cout << "Average: " << accumulate(marks.begin(), marks.end(), 0.0) / marks.size() << '\\n';
    cout << "Roll 2: " << rollToName[2] << ", Riya: " << nameToMarks["Riya"] << '\\n';
}
