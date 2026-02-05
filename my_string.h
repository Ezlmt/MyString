#pragma once
#include <cstddef>
class MyString {

public:
  MyString();
  MyString(const char* s);
  MyString(const MyString& other);
  ~MyString();

  MyString& operator=(const MyString& other);
  MyString& operator+=(const MyString& other);
  MyString operator+(const MyString& other) const;
  char& operator[](size_t index);
  const char& operator[](size_t index) const;
  void swap(MyString& other) noexcept;

  size_t size() const;
  const char* c_str() const;
private:
  char* data_;
  size_t size_;
  size_t cap_;

  static size_t cstr_length(const char* s);
  static void cstr_copy(char* dst, const char* src, size_t n);
  void init_from(const char* src, size_t len);
};
