#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class Stack {
    vector<T> items;
public:
    void push(const T& value) { items.push_back(value); }
    void pop() {
        if (empty()) throw underflow_error("Cannot pop an empty stack");
        items.pop_back();
    }
    T& top() {
        if (empty()) throw underflow_error("Stack is empty");
        return items.back();
    }
    bool empty() const { return items.empty(); }
    size_t size() const { return items.size(); }
};

template <typename T>
void testStack(T a, T b) {
    Stack<T> stack;
    stack.push(a); stack.push(b);
    cout << "Top: " << stack.top() << ", size: " << stack.size() << '\n';
    stack.pop();
    cout << "After pop: " << stack.top() << '\n';
}

int main() {
    testStack<int>(10, 20);
    testStack<float>(1.5f, 2.5f);
    testStack<string>("hello", "C++");
}
