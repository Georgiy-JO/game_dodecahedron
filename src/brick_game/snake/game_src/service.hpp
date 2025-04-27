#pragma once
#include <iostream>
#include "../logger/logger.hpp"

namespace s21 {
using u_int = unsigned int;
using coords_t = std::pair<u_int, u_int>;

class snakeError_ : public std::exception {
  int code;
  std::string msg;

 public:
  snakeError_(int cd=0, const char* error = "Unknown error.") :code(cd), msg(error) {}
  snakeError_(const snakeError_& other) :code(other.code), msg(other.msg) {}
  inline const char* what() const noexcept override { return msg.c_str(); }
  inline int getCode() const noexcept { return code; }
};
class FileOpenError : public snakeError_ {
 public:
  FileOpenError(int cd=1, const char* error = "File was not open or can not be found.")
      : snakeError_(cd, error) {}
};
class InputError : public snakeError_ {
 public:
  InputError(int cd=2,const char* error = "User input error.") : snakeError_(cd, error) {}
};
class OutOfRangeError : public snakeError_ {
 public:
 OutOfRangeError(int cd=3, const char* error = "Value is out of range") : snakeError_(cd, error) {}
};

}  // namespace s21