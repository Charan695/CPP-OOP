#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Sensor {
    int id;
    explicit Sensor(int value) : id(value) { cout << "Sensor " << id << " created\\n"; }
    ~Sensor() { cout << "Sensor " << id << " destroyed\\n"; }
};

int main() {
    {
        auto uniqueSensor = make_unique<Sensor>(1);
        cout << "Unique owner uses sensor " << uniqueSensor->id << '\\n';
    }
    {
        auto first = make_shared<Sensor>(2);
        {
            auto second = first;
            cout << "Shared owners: " << first.use_count() << '\\n';
        }
        cout << "Owners after inner scope: " << first.use_count() << '\\n';
    }
    vector<unique_ptr<int>> values;
    for (int i = 0; i < 10000; ++i) values.push_back(make_unique<int>(i));
    cout << "Managed integers: " << values.size()
         << "\\nRAII releases resources automatically at scope exit.\\n";
}
