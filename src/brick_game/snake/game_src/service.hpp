#pragma once
#include <iostream>

namespace s21 {
/**
 * @brief Type alias for unsigned int.
 */
using u_int = unsigned int;

/**
 * @brief Type alias for coordinate pairs (x, y) using unsigned integers.
 */
using coords_t = std::pair<u_int, u_int>;

/**
 * @brief Base class for all Snake-related exceptions.
 * Inherits from std::exception and carries an error code (new for
 * std::exception) and message.
 */
class snakeError_ : public std::exception {
  int code;         ///< Error code.
  std::string msg;  ///< Error message.

 public:
  /**
   * @brief Constructs a snakeError_ with a given code and message.
   * @param cd Error code (default: 0).
   * @param error Error message (default: "Unknown error.").
   */
  snakeError_(int cd = 0, const char* error = "Unknown error.")
      : code(cd), msg(error) {}

  /**
   * @brief Copy constructor.
   * @param other Another snakeError_ instance to copy from.
   */
  snakeError_(const snakeError_& other) : code(other.code), msg(other.msg) {}

  /**
   * @brief Retrieves the error message.
   * @return C-string containing the error message.
   */
  inline const char* what() const noexcept override { return msg.c_str(); }

  /**
   * @brief Retrieves the error code.
   * @return Integer representing the error code.
   */
  inline int getCode() const noexcept { return code; }
};

/**
 * @brief Exception for file opening errors.
 * Inherits from snakeError_.
 */
class FileOpenError : public snakeError_ {
 public:
  /**
   * @brief Constructs a FileOpenError with a code and message.
   * @param cd Error code is 1 (can be changed in use).
   * @param error Error message: "File was not open or can not be found." (can
   * be changed in use).
   */
  FileOpenError(int cd = 1,
                const char* error = "File was not open or can not be found.")
      : snakeError_(cd, error) {}
};

/**
 * @brief Exception for invalid user input.
 * Inherits from snakeError_.
 */
class InputError : public snakeError_ {
 public:
  /**
   * @brief Constructs an InputError with a code and message.
   * @param cd Error code: 2.
   * @param error Error message: "User input error.".
   */
  InputError(int cd = 2, const char* error = "User input error.")
      : snakeError_(cd, error) {}
};

/**
 * @brief Exception for values that are out of range.
 * Inherits from snakeError_.
 */
class OutOfRangeError : public snakeError_ {
 public:
  /**
   * @brief Constructs an OutOfRangeError with a code and message.
   * @param cd Error code: 3.
   * @param error Error message: "Value is out of range".
   */
  OutOfRangeError(int cd = 3, const char* error = "Value is out of range")
      : snakeError_(cd, error) {}
};

}  // namespace s21