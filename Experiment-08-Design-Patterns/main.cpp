#include <iostream>
#include <string>
using namespace std;

// Singleton is useful for a single shared service such as a logger.
// Trade-off: global access can make testing and dependencies harder.
class Logger {
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
public:
    static Logger& instance() {
        static Logger logger; // Thread-safe initialization since C++11.
        return logger;
    }
    void log(const string& message) const { cout << "[LOG] " << message << '\n'; }
};

int main() {
    Logger::instance().log("Application started");
    Logger::instance().log("Student record processed");
}
