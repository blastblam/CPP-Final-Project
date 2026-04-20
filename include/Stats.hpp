#ifndef STATS_HPP
#define STATS_HPP

#include <iostream>

class Stats {
private:
    int hp;
    int maxHp;
    int attack;
    int defense;
    int speed;

public:
    Stats(int hp = 0, int attack = 0, int defense = 0, int speed = 0);

    int getHp() const;
    int getMaxHp() const;
    int getAttack() const;
    int getDefense() const;
    int getSpeed() const;

    void setHp(int value);
    void setMaxHp(int value);
    void setAttack(int value);
    void setDefense(int value);

    Stats operator+(const Stats& other) const;
    Stats operator-(const Stats& other) const;
    bool operator==(const Stats& other) const;
    bool operator<(const Stats& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Stats& stats);
};

#endif
