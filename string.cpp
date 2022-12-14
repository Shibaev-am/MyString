#include "string.h"
#include <algorithm>
#include <cstring>
#include <iostream>

void String::swap(String& lhs, String& rhs) {
    std::swap(lhs.string_, rhs.string_);
    std::swap(lhs.size_, rhs.size_);
    std::swap(lhs.capacity_, rhs.capacity_);
}

String::String() : size_(0), capacity_(0), string_(new char[1]) {
    string_[0] = '\0';
}

String::String(const char* arr)
    : size_(strlen(arr)),
      capacity_(strlen(arr)),
      string_(new char[strlen(arr) + 1]) {
    std::copy(arr, arr + size_ + 1, string_);
}

String::String(int n, char c)
    : size_(n), capacity_(n), string_(new char[n + 1]) {
    std::fill(string_, string_ + n, c);
    string_[n] = '\0';
}

String::String(const String& copy)
    : size_(copy.size_), capacity_(size_), string_(new char[capacity_ + 1]) {
    std::copy(copy.string_, copy.string_ + size_ + 1, string_);
}

size_t String::length() const {
    return size_;
}

size_t String::size() const {
    return size_;
}

size_t String::capacity() const {
    return capacity_;
}

const char& String::operator[](size_t pos) const {
    return string_[pos];
}

char& String::operator[](size_t pos) {
    return string_[pos];
}

const char& String::front() const {
    return string_[0];
}

char& String::front() {
    return string_[0];
}

const char& String::back() const {
    return string_[size_ - 1];
}

char& String::back() {
    return string_[size_ - 1];
}

bool String::empty() const {
    return (size_ == 0);
}

void String::clear() {
    size_ = 0;
}

const char* String::data() const {
    return string_;
}

char* String::data() {
    return string_;
}

String::~String() {
    delete[] string_;
}

String& String::operator=(String other) {
    swap(*this, other);
    return *this;
}

String& String::operator+=(const String& other) {
    if (size_ + other.size_ < capacity_) {
        std::copy(other.string_, other.string_ + other.size_ + 1,
                  string_ + size_);
        size_ += other.size_;
        return *this;
    }
    char* str = new char[size_ + other.size_ + 1];
    size_t new_size = size_ + other.size_;
    size_t new_capacity = size_ + other.size_;
    std::copy(string_, string_ + size_, str);
    std::copy(other.string_, other.string_ + other.size_ + 1, str + size_);
    size_ = new_size;
    capacity_ = new_capacity;
    delete[] string_;
    string_ = str;
    return *this;
}

String& String::operator+=(char other) {
    push_back(other);
    return *this;
}

void String::push_back(char c) {
    if (size_ == capacity_ && capacity_ > 0) {
        capacity_ *= 2;
        realloc(capacity_);
        string_[size_] = c;
        string_[size_ + 1] = '\0';
        ++size_;
    } else if (size_ == capacity_ && capacity_ == 0) {
        capacity_ = 1;
        size_ = 1;
        realloc(capacity_ + 1);
        string_[0] = c;
        string_[1] = '\0';
    } else {
        string_[size_++] = c;
    }
}

void String::pop_back() {
    string_[--size_] = '\0';
}

size_t String::find(const String& substring) const {
    return find(substring, 0, size_ - substring.size_ + 1, 1);
}

size_t String::rfind(const String& substring) const {
    return find(substring, size_ - substring.size_, -1, -1);
}

size_t String::find(const String& substring, int start, int fin, int f) const {
    int i = start;
    while (i != fin) {
        bool flag = true;
        for (size_t j = 0; j < substring.size_; ++j) {
            if (string_[i + j] != substring.string_[j]) {
                flag = false;
            }
        }
        if (flag) {
            return i;
        }
        i += f;
    }
    return size_;
}

String String::substr(size_t start, size_t count) const {
    String ans(count, 'a');
    if (start + count <= size_) {
        std::copy(string_ + start, string_ + start + count, ans.string_);
    }
    return ans;
}

void String::shrink_to_fit() {
    if (size_ + 1 < capacity_) {
        capacity_ = size_;
        realloc(size_ + 1);
    }
}

void String::realloc(size_t new_size) {
    char* new_arr = new char[new_size];
    std::copy(string_, string_ + size_ + 1, new_arr);
    delete[] string_;
    string_ = new_arr;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
    for (size_t i = 0; i < string.size(); ++i) {
        os << string[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& obj) {
    String ans;
    char c = 'a';
    while (is.get(c) && c != ' ' && c != '\n' && c != '\t') {
        ans.push_back(c);
    }
    obj = ans;
    return is;
}

String operator+(const String& lhs, const String& rhs) {
    String tmp = lhs;
    tmp += rhs;
    return tmp;
}

String operator+(char lhs, const String& rhs) {
    String tmp;
    tmp += lhs;
    tmp += rhs;
    return tmp;
}

String operator+(const String& lhs, char rhs) {
    String tmp = lhs;
    tmp += rhs;
    return tmp;
}

bool operator<(const String& lhs, const String& rhs) {
    size_t i = 0;
    while (i <= lhs.size() && i <= rhs.size()) {
        if (lhs[i] >= rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

bool operator>=(const String& lhs, const String& rhs) {
    return !(lhs < rhs);
}

bool operator>(const String& lhs, const String& rhs) {
    return (rhs < lhs);
}

bool operator<=(const String& lhs, const String& rhs) {
    return !(lhs > rhs);
}

bool operator==(const String& lhs, const String& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    size_t i = 0;
    while (i <= lhs.size() && i <= rhs.size()) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}
