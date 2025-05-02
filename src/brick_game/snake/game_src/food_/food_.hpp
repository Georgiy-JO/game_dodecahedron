#pragma once

#include "../service.hpp"

namespace s21 {
/**
 * @brief Represents a general food item with a position and value.
 */
class food_ {
 private:
  coords_t position;  ///< Position of the food item on the field.
  const int val;      ///< Value of the food item.

 public:
  /**
   * @brief Constructs a food item with an optional value.
   * @param V The value of the food item. Defaults to 0.
   */
  food_(int V = 0);
  /**
   * @brief Constructs a food item at a specific position with an optional
   * value.
   * @param x X-coordinate of the food item.
   * @param y Y-coordinate of the food item.
   * @param V The value of the food item. Defaults to 0.
   */
  food_(u_int x, u_int y, int V = 0);

  /**
   * @brief Sets the position of the food item.
   * @param x New X-coordinate.
   * @param y New Y-coordinate.
   */
  void setPosition(u_int x, u_int y);
  /**
   * @brief Retrieves the current position of the food item.
   * @return Position as a coords_t.
   */
  coords_t getPosition() const;
  /**
   * @brief Retrieves the value of the food item.
   * @return Integer value.
   */
  int getValue() const;
};

/**
 * @brief Represents an "insect", a specific type of food with fixed value.
 * @note Insects always have a value of 1.
 */
class insect_ : public food_ {
 private:
  static constexpr int VALUE = 1;  ///< Constant value for "insect".

 public:
  /**
   * @brief Constructs an "insect" at default position.
   */
  insect_();
  /**
   * @brief Constructs an "insect" at a specific position.
   * @param x X-coordinate of the "insect".
   * @param y Y-coordinate of the "insect".
   */
  insect_(u_int x, u_int y);
};

/**
 * @brief Represents a "mouse", a specific type of food with fixed value.
 * @note Mice always have a value of 2.
 */
class mouse_ : public food_ {
 private:
  static constexpr int VALUE = 2;  ///< Constant value for "mouse".

 public:
  /**
   * @brief Constructs a "mouse" at default position.
   */
  mouse_();
  /**
   * @brief Constructs a "mouse" at a specific position.
   * @param x X-coordinate of the "mouse".
   * @param y Y-coordinate of the "mouse".
   */
  mouse_(u_int x, u_int y);
};
}  // namespace s21