#include <iostream>
#include <memory>

#include "Battle.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Stats.hpp"

int main() {
    try {
        Player hero("Arin", Stats(45, 12, 4, 7));
        Battle battle(hero);

        battle.addEnemy(std::make_unique<Enemy>("Slime", Stats(18, 5, 1, 2)));
        battle.addEnemy(std::make_unique<Enemy>("Goblin", Stats(22, 7, 2, 4)));
        battle.addEnemy(std::make_unique<Enemy>("Orc", Stats(30, 9, 3, 3)));

        std::cout << "Welcome to the turn-based battle game.\n";
        battle.run();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
