#pragma once
#include <iostream>

namespace s21 {
using u_int = unsigned int;
using coords_t = std::pair<u_int, u_int>;

class snakeError_ : public std::exception {
  std::string msg;

 public:
  snakeError_(const char* error = "Unknown error.") : msg(error) {}
  snakeError_(const snakeError_& other) : msg(other.msg) {}
  inline const char* what() const noexcept override { return msg.c_str(); }
};
class FileOpenError : public snakeError_ {
 public:
  FileOpenError(const char* error = "File was not open or can not be found.")
      : snakeError_(error) {}
};
class InputError : public snakeError_ {
 public:
  InputError(const char* error = "User input error.") : snakeError_(error) {}
};
class OutOfRangeError : public snakeError_ {
 public:
 OutOfRangeError(const char* error = "Value is out of range") : snakeError_(error) {}
};

}  // namespace s21