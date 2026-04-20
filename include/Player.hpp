#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"

class Player : public Character {
public:
    Player(const std::string& name, const Stats& stats);
    int computeDamage() const override;
    std::string getRole() const override;
    void gainStats(int hpGain, int atkGain, int defGain, int hpCap, int atkCap, int defCap);
};

#endif
