#include "Stats.hpp"

Stats::Stats(int hp, int attack, int defense, int speed)
    : hp(hp), maxHp(hp), attack(attack), defense(defense), speed(speed) {}

int Stats::getHp() const { return hp; }
int Stats::getMaxHp() const { return maxHp; }
int Stats::getAttack() const { return attack; }
int Stats::getDefense() const { return defense; }
int Stats::getSpeed() const { return speed; }

void Stats::setHp(int value) { hp = value; }
void Stats::setMaxHp(int value) { maxHp = value; }
void Stats::setAttack(int value) { attack = value; }
void Stats::setDefense(int value) { defense = value; }

Stats Stats::operator+(const Stats& other) const {
    return Stats(hp + other.hp, attack + other.attack, defense + other.defense, speed + other.speed);
}

Stats Stats::operator-(const Stats& other) const {
    return Stats(hp - other.hp, attack - other.attack, defense - other.defense, speed - other.speed);
}

bool Stats::operator==(const Stats& other) const {
    return hp == other.hp && attack == other.attack && defense == other.defense && speed == other.speed;
}

bool Stats::operator<(const Stats& other) const {
    return hp + attack + defense + speed < other.hp + other.attack + other.defense + other.speed;
}

std::ostream& operator<<(std::ostream& os, const Stats& stats) {
    os << "HP=" << stats.hp
       << ", ATK=" << stats.attack
       << ", DEF=" << stats.defense
       << ", SPD=" << stats.speed;
    return os;
}
