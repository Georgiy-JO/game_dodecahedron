
#include "timer_.hpp"

namespace s21 {
timer_::timer_() : last_update(clock::now()) {}
void timer_::setSpeed(u_int speed_) {
  if (speed_ < 10) speed = speed_;
}
void timer_::updateSpeed() {
  if (speed < 9) speed++;
}
int timer_::getSpeed() const { return speed; }
u_int timer_::getMovesNumber() {
  auto time_now = clock::now();
  auto time_delta = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_now - last_update)
                        .count();
  u_int moves_number = time_delta / SPEED_TO_INTERVAL[speed];
  if (moves_number > 0)
    last_update +=
        std::chrono::milliseconds(moves_number * SPEED_TO_INTERVAL[speed]);
  else
    moves_number = 0;
  return moves_number;
}
void timer_::reset() { last_update = clock::now(); }
void timer_::totalReset() {
  speed = 0;
  reset();
}

}  // namespace s21