#pragma once

#include <deque>

#include "../service.hpp"

namespace s21 {
/**
 * @brief Represents the Snake in the game, including its body, direction of
 * movement, and behavior.
 */
class snake_ {
 public:
  /**
   * @brief Enumerates possible movement directions for the snake.
   * @enum Directions
   */
  enum Directions {
    Up,     ///< Move upward.
    Right,  ///< Move to the right.
    Down,   ///< Move downward.
    Left    ///< Move to the left.
  };

  /**
   * @brief Type alias for a coordinate pair (x, y) for snake nodes.
   */
  using node_ = std::pair<int, int>;

 private:
  static constexpr int def_length = 4;  ///< Default starting snake length.
  std::deque<node_> nodes;  ///< Container holding the snake's body segments.
  int direction = Down;     ///< Stores current movement direction of the snake.

 public:
  /**
   * @brief Constructs a snake at default position.
   * @note standart starting snake length is 4.
   */
  snake_();

  /**
   * @brief Constructs a snake at a given starting position.
   * @param x_begining X-coordinate of the starting position.
   * @param y_begining Y-coordinate of the starting position.
   */
  snake_(int x_begining, int y_begining);

  /**
   * @brief Retrieves the current size (length) of the snake.
   * @return Number of segments in the snake.
   */
  u_int getSize() const;

  /**
   * @brief Accesses a specific segment of the snake.
   * @param index Index of the segment.
   * @return Coordinate pair of the segment coordinates at the given index.
   */
  node_ operator[](u_int index) const;

  /**
   * @brief Moves the snake in the current direction.
   * @note first segment is moved forward, second one takes its place etc.
   */
  void snakeMove();

  /**
   * @brief Changes the snake's direction based on input.
   * @param change The direction of the turn: Directions::Right or
   * Directions::Left.
   */
  void changeDirection(int change);

  /**
   * @brief Move the snake in the current direction by growing.
   * @note New segment appear in the current direction (at the snakes head).
   */
  void snakeGrow();

  /**
   * @brief Retrieves the head (front segment) of the snake.
   * @return Coordinate pair of the head.
   */
  node_ getHead() const;

  /**
   * @brief Gets the current direction the snake is moving.
   * @return Direction as an integer (from Directions enum).
   */
  int getDirection() const;

  /**
   * @brief Resets the snake to a new starting position with a standart starting
   * length.
   * @param x_begining New X-coordinate.
   * @param y_begining New Y-coordinate.
   */
  void reset(int x_begining, int y_begining);

  /**
   * @brief Checks if the snake has collided with itself.
   * @return True if the snake's head intersects its body.
   */
  bool selfCrash() const;
};

}  // namespace s21