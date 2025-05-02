#pragma once

#include <chrono>

#include "../service.hpp"

namespace s21 {
/**
 * @brief A timer class for tracking time-based game movement and controlling
 * the speed.
 */
class timer_ {
  /**
   * @brief Type alias for std::chrono::steady_clock for simplicity of code
   * reading.
   */
  using clock = std::chrono::steady_clock;

 public:
  /**
   * @brief Maximum game speed setting.
   * @note Speeds range from 0 (slowest) to 9 (fastest).
   */
  static constexpr int MAX_SPEED = 9;  // from 0 to 9 - 10 speeds

 private:
  /**
   * @brief Predefined intervals in milliseconds for each speed level.
   * @note Lower values correspond to faster game actions.
   */
  static constexpr u_int SPEED_TO_INTERVAL[10] = {500, 450, 400, 375, 350,
                                                  325, 300, 250, 200, 100};
  clock::time_point last_update;  ///< Timestamp of the last movement update.
  int speed = 0;                  ///< Current game speed (0 to MAX_SPEED).

 public:
  /**
   * @brief Constructs the timer and sets the interval begining.
   */
  timer_();
  /**
   * @brief Sets the timer speed.
   * @param speed A value between 0 and MAX_SPEED.
   */
  void setSpeed(u_int speed_);
  /**
   * @brief Increases the timer speed by one if not at maximum.
   */
  void updateSpeed();
  /**
   * @brief Retrieves the current speed level.
   * @return The current speed as an integer.
   */
  int getSpeed() const;
  /**
   * @brief Calculates the number of moves that should be processed since the
   * last update.
   * @return Number of moves that have passed.
   */
  u_int getMovesNumber();
  /**
   * @brief Updates the internal timer checkpoint (last_update) without changing
   * speed.
   */
  void reset();
  /**
   * @brief Resets both the internal timer and speed to initial state.
   */
  void totalReset();
};
}  // namespace s21