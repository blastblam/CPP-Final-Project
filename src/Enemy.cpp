#include "Enemy.hpp"

Enemy::Enemy(const std::string& name, const Stats& stats)
    : Character(name, stats) {}

int Enemy::computeDamage() const {
    return stats.getAttack();
}

std::string Enemy::getRole() const {
    return "Enemy";
}
