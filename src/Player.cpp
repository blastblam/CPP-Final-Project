#include "Player.hpp"

Player::Player(const std::string& name, const Stats& stats)
    : Character(name, stats) {}

int Player::computeDamage() const {
    return stats.getAttack() + 3;
}

std::string Player::getRole() const {
    return "Hero";
}
