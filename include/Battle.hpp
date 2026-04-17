#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <deque>
#include <map>
#include <memory>
#include <string>
#include "Enemy.hpp"
#include "GameExceptions.hpp"
#include "Player.hpp"

class Battle {
private:
    Player player;
    std::deque<std::unique_ptr<Character>> enemies;
    std::map<int, std::string> commands;

    void printStatus() const;
    int chooseEnemyTarget() const;
    void playerTurn();
    void enemyTurn();
    bool allEnemiesDefeated() const;
    int calculateFinalDamage(const Character& attacker, const Character& defender) const;

public:
    explicit Battle(const Player& player);
    ~Battle();

    void addEnemy(std::unique_ptr<Character> enemy);
    void run();
};

#endif
