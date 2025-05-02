#pragma once

#include <memory>

#include "../food_/food_.hpp"
#include "../randGen_/randGen_.hpp"
#include "../snake_/snake_.hpp"

namespace s21 {
/**
 * @brief Represents the game field where the snake moves and interacts with
 * food.
 */
class field_ {
 public:
  /**
   * @brief Width of the game field.
   */
  static constexpr int WIDTH = 10;
  /**
   * @brief Height of the game field.
   */
  static constexpr int HEIGHT = 20;

 private:
  snake_ snake;                 ///< The snake instance on the field.
  std::unique_ptr<food_> food;  ///< Pointer to the current food object.
  randGen_ rand_gen;            ///< Random number generator for food placement.

 public:
  /**
   * @brief Constructs the game field, set the snake on it, initializes random
   * generator and spawn food.
   */
  field_();
  /**
   * @brief Spawns a new random food object at a random position.
   */
  void spawnFood();
  /**
   * @brief Checks if the snake is about to eat food with its next move.
   * @return True if food will be eaten; otherwise false.
   */
  bool checkForFood() const;
  /**
   * @brief Checks if the snake has crashed (inc. into itself and field
   * borders).
   * @return True if a crash occurred; otherwise false.
   */
  bool checkForCrash() const;
  /**
   * @brief Moves the snake in the current direction and eats food if it is in
   * the way.
   * @return True if due the move it ate food; false if no food was eaten.
   */
  bool moveSnake();
  /**
   * @brief Turns the snake to the right.
   */
  void snakeTurnRight();
  /**
   * @brief Turns the snake to the left.
   */
  void snakeTurnLeft();
  /**
   * @brief Gets the value of the current food.
   * @return An integer representing the food's value.
   */
  int getFoodValue() const;
  /**
   * @brief Checks if the entire field is filled with the snake.
   * @note The field is called full if snake_length = field_height*field_width.
   * @return True if snake covered all the field blocks; otherwise false.
   */
  bool isFieldFull() const;
  /**
   * @brief Resets the field, including the snake and food state.
   */
  void reset();
  /**
   * @brief Retrieves the value of a block at a specific position on the field.
   * @param x The horizontal position.
   * @param y The vertical position.
   * @return An integer representing the field content at (x, y).
   *         The value depends on if the field block is free, is it occupied by
   * snake, is it taken by food (the kind of food does value).
   */
  int operator()(int x, int y) const;
};

}  // namespace s21