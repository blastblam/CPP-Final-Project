#ifndef DRAGON_HPP
#define DRAGON_HPP

#include "Enemy.hpp"

class Dragon : public Enemy {
public:
    Dragon();
    int computeDamage() const override;
    std::string getRole() const override;
};

#endif
