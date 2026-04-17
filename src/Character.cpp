#include "Character.hpp"

Character::Character(const std::string& name, const Stats& stats)
    : name(name), stats(stats) {}

Character::~Character() = default;

std::string Character::getName() const {
    return name;
}

Stats Character::getStats() const {
    return stats;
}

bool Character::isAlive() const {
    return stats.getHp() > 0;
}

void Character::takeDamage(int damage) {
    int newHp = stats.getHp() - damage;
    if (newHp < 0) {
        newHp = 0;
    }
    stats.setHp(newHp);
}
