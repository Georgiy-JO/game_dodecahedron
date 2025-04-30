
#include "food_.hpp"

namespace s21 {
food_::food_(int V) : position(0, 0), val(V) {}
food_::food_(u_int x, u_int y, int V) : position(x, y), val(V) {}
void food_::setPosition(u_int x, u_int y) { position = std::pair{x, y}; }
coords_t food_::getPosition() const { return position; }
int food_::getValue() const { return val; }

insect_::insect_() : food_(VALUE) {}
insect_::insect_(u_int x, u_int y) : food_(x, y, VALUE) {}

mouse_::mouse_() : food_(VALUE) {}
mouse_::mouse_(u_int x, u_int y) : food_(x, y, VALUE) {}
}  // namespace s21