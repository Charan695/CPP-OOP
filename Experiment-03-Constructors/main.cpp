#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

class Buffer {
    size_t size_;
    int* data_;
public:
    Buffer() : size_(0), data_(nullptr) { cout << "Default constructor\\n"; }
    explicit Buffer(size_t n) : size_(n), data_(n ? new int[n]{} : nullptr) {
        cout << "Parameterized constructor\\n";
    }
    Buffer(const Buffer& other) : size_(other.size_), data_(size_ ? new int[size_] : nullptr) {
        if (size_) copy(other.data_, other.data_ + size_, data_);
        cout << "Copy constructor\\n";
    }
    Buffer(Buffer&& other) noexcept
        : size_(exchange(other.size_, 0)), data_(exchange(other.data_, nullptr)) {
        cout << "Move constructor\\n";
    }
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;
        int* fresh = other.size_ ? new int[other.size_] : nullptr;
        if (other.size_) copy(other.data_, other.data_ + other.size_, fresh);
        delete[] data_;
        data_ = fresh;
        size_ = other.size_;
        cout << "Copy assignment\\n";
        return *this;
    }
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = exchange(other.data_, nullptr);
        size_ = exchange(other.size_, 0);
        cout << "Move assignment\\n";
        return *this;
    }
    ~Buffer() { delete[] data_; cout << "Destructor\\n"; }
    void set(size_t i, int value) { if (i < size_) data_[i] = value; }
    void display() const {
        for (size_t i = 0; i < size_; ++i) cout << data_[i] << ' ';
        cout << '\\n';
    }
};

int main() {
    Buffer first(3);
    first.set(0, 10); first.set(1, 20); first.set(2, 30);
    Buffer copied(first);
    Buffer moved(std::move(copied));
    Buffer assigned;
    assigned = first;
    Buffer moveAssigned;
    moveAssigned = std::move(assigned);
    moved.display();
    moveAssigned.display();
}
