#include <algorithm>
#include "Player.hpp"

Player::Player(const std::string& name, const Stats& stats)
    : Character(name, stats) {}

int Player::computeDamage() const {
    return stats.getAttack() + 3;
}

std::string Player::getRole() const {
    return "Hero";
}

void Player::gainStats(int hpGain, int atkGain, int defGain, int hpCap, int atkCap, int defCap) {
    int newMaxHp = std::min(stats.getMaxHp() + hpGain, hpCap);
    stats.setMaxHp(newMaxHp);
    stats.setHp(newMaxHp);  // fully restore HP to new max on victory
    stats.setAttack(std::min(stats.getAttack() + atkGain, atkCap));
    stats.setDefense(std::min(stats.getDefense() + defGain, defCap));
}
