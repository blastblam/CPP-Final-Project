#include "Dragon.hpp"

Dragon::Dragon() : Enemy("Dragon", Stats(75, 16, 7, 5)) {}

// Boss trait: deals 1.5x damage
int Dragon::computeDamage() const {
    return static_cast<int>(getStats().getAttack() * 1.5);
}

std::string Dragon::getRole() const {
    return "Boss";
}
