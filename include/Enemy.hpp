#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.hpp"

class Enemy : public Character {
public:
    Enemy(const std::string& name, const Stats& stats);
    int computeDamage() const override;
    std::string getRole() const override;
};

#endif
