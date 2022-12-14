#pragma once
#include <algorithm>
#include <cstring>
#include <iostream>

class String {
  private:
    size_t size_, capacity_;
    char* string_;
    static void swap(String& lhs, String& rhs);
    size_t find(const String& substring, int start, int fin, int f) const;
    void realloc(size_t new_size);

  public:
    String();
    String(const char* arr);
    String(int n, char c);
    String(const String& copy);
    size_t length() const;
    size_t size() const;
    size_t capacity() const;
    String& operator=(String other);
    String& operator+=(const String& other);
    String& operator+=(char other);
    const char& operator[](size_t pos) const;
    char& operator[](size_t pos);
    void push_back(char c);
    void pop_back();
    const char& front() const;
    char& front();
    const char& back() const;
    char& back();
    size_t find(const String& substring) const;
    size_t rfind(const String& substring) const;
    String substr(size_t start, size_t count) const;
    bool empty() const;
    void clear();
    void shrink_to_fit();
    const char* data() const;
    char* data();
    ~String();
};

std::ostream& operator<<(std::ostream& os, const String& string);

std::istream& operator>>(std::istream& is, String& obj);

String operator+(const String& lhs, const String& rhs);

String operator+(char lhs, const String& rhs);

String operator+(const String& lhs, char rhs);

bool operator<(const String& lhs, const String& rhs);

bool operator>=(const String& lhs, const String& rhs);

bool operator>(const String& lhs, const String& rhs);

bool operator<=(const String& lhs, const String& rhs);

bool operator==(const String& lhs, const String& rhs);

bool operator!=(const String& lhs, const String& rhs);
