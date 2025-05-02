#pragma once

#include <chrono>
#include <random>

namespace s21 {
/**
 * @brief Random generator utility class for generating coordinates and binary
 * values.
 */
class randGen_ {
 private:
  /**
   * @brief Probability constant for binary generation.
   * @note Used to determing a probability of one output against another
   *       in this case 1 chances are 1/5 (0 - 4/5).
   */
  static constexpr int binary_kind_chance = 5;

  std::mt19937 mt;  ///< Mersenne Twister random number generator.
  std::uniform_int_distribution<u_int>
      x_dist;  ///< Distribution for X coordinates.
  std::uniform_int_distribution<u_int>
      y_dist;  ///< Distribution for Y coordinates.
  std::uniform_int_distribution<char>
      binary;  ///< Distribution for binary values.

 public:
  /**
   * @brief Constructs a random generator with defined width and height
   * boundaries.
   * @param WIDTH_ Maximum value (exclusive) for X coordinate.
   * @param HEIGHT_ Maximum value (exclusive) for Y coordinate.
   */
  randGen_(u_int WIDTH_, u_int HEIGHT_);

  /**
   * @brief Generates a random X coordinate within the initialized range.
   * @return Random unsigned integer X value.
   */
  u_int getX();

  /**
   * @brief Generates a random Y coordinate within the initialized range.
   * @return Random unsigned integer Y value.
   */
  u_int getY();

  /**
   * @brief Generates a random binary value.
   * @return Random char value representing binary data.
   */
  char getBinary();
};
}  // namespace s21