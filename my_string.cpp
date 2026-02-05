#include "my_string.h"
#include <cassert>
#include <cstddef>
#include <iostream>

MyString::MyString()
  : data_(nullptr), size_(0), cap_(0)
{
  data_ = new char[1];
  data_[0] = '\0';
  cap_ = 0;
}

MyString::~MyString()
{
  delete [] data_;
}

void MyString::init_from(const char* src, size_t len)
{
  data_ = new char[len + 1];
  cstr_copy(data_, src, len);
  data_[len] = '\0';

  size_ = len;
  cap_ = len;
}

MyString::MyString(const char* s)
  : data_(nullptr), size_(0), cap_(0)
{
  if (s == nullptr) {
    data_ = new char[1];
    data_[0] = '\0';
    cap_ = 0;
  } else {
    size_t len = cstr_length(s);
    init_from(s, len);
  }
}

MyString::MyString(const MyString& other) 
  : data_(nullptr), size_(0), cap_(0)
{
  init_from(other.data_, other.size_);
}

size_t MyString::size() const
{
  return size_;
}

const char* MyString::c_str() const
{
  return data_;
}

size_t MyString::cstr_length(const char* s) {
  size_t len = 0;
  while (s[len] != '\0') {
    ++ len;
  }
  return len;
}

void MyString::cstr_copy(char* dst, const char* src, size_t n) {
  for (size_t i=0; i<n; i++) {
    dst[i] = src[i];
  }
}

MyString& MyString::operator=(const MyString& other){
  MyString temp(other);
  swap(temp);
  return *this;
}

void MyString::swap(MyString& other) noexcept {
  char* data_tmp = other.data_;
  size_t size_tmp = other.size_;
  size_t cap_tmp = other.cap_;

  other.data_ = this->data_;
  other.size_ = this->size_;
  other.cap_ = this->cap_;

  this->data_ = data_tmp;
  this->cap_ = cap_tmp;
  this->size_ = size_tmp;
}

char& MyString::operator[](size_t index) {
  assert(index < size_);
  return this->data_[index];
}

bool MyString::operator==(const MyString& other) const {
  return cstr_equal(this->data_, other.data_);
}

bool MyString::operator!=(const MyString& other) const {
  return !(*this == other);
}

const char& MyString::operator[](size_t index) const {
  assert(index < size_);
  return this->data_[index];
}

MyString& MyString::operator+=(const MyString& other) {
  size_t size_new = this->size_ + other.size_;

  if (size_new > this->cap_) {
    reserve(size_new * 2);
  }

  cstr_copy(data_ + size_, other.data_, other.size_);

  size_ = size_new;
  data_[size_] = '\0';

  return *this;
}

MyString MyString::operator+(const MyString& other) const{
  MyString res = *this;
  res += other;
  return res;
};

bool MyString::empty() const {
  return this->size_ == 0;
}

void MyString::clear() {
  this->size_ = 0;
  this->data_[0] = '\0';
}
void MyString::reserve(size_t new_cap) {
  if (new_cap <= cap_) {
    return;
  }
  
  char* new_data_ = new char[new_cap + 1];
  
  cstr_copy(new_data_, this->data_, this->size_);
  
  new_data_[this->size_] = '\0';
  
  delete[] this->data_;

  this->cap_ = new_cap;
  this->data_ = new_data_;
}


bool cstr_equal(const char* a, const char* b) {
  size_t i = 0;
  while ( a[i] != '\0' && b[i] != '\0') {
    if (a[i] != b[i]) {
      return false;
    }
    ++i;
  }
  return a[i] == b[i];
}

int main() {
  MyString a;
  MyString b("hello");
  MyString c(b);

  a = c;

  char cc = a[2];
  std::cout << cc << std::endl;

  std::cout << b.size() << std::endl;
  std::cout << a.c_str() << std::endl;
  assert(cstr_equal(b.c_str(), "hello"));
  assert(cstr_equal(b.c_str(), c.c_str()));
  assert(cstr_equal(a.c_str(), c.c_str()));

  MyString d("123456");
  d[5] = 'a';
  std::cout << d.c_str() << std::endl;
  d += "bbb";
  std::cout << d.c_str() << std::endl;
  MyString e = a + d;
  std::cout << e.c_str() << std::endl;

  std::cout << (a == b) << std::endl;
  std::cout << (a != d) << std::endl;

}
