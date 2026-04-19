#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include "Stats.hpp"

class Character {
protected:
    std::string name;
    Stats stats;

public:
    Character(const std::string& name, const Stats& stats);
    virtual ~Character();

    std::string getName() const;
    Stats getStats() const;
    bool isAlive() const;
    void takeDamage(int damage);
    void heal(int amount);

    virtual int computeDamage() const = 0;
    virtual std::string getRole() const = 0;
};

#endif
