#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "Battle.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Stats.hpp"

int main() {
    try {
        Player hero("Arin", Stats(45, 12, 4, 7));

        // Enemies listed in ascending order of strength
        struct EnemyDef { const char* name; Stats stats; };
        std::vector<EnemyDef> roster = {
            {"Slime",  Stats(18, 5, 1, 2)},
            {"Goblin", Stats(22, 7, 2, 4)},
            {"Orc",    Stats(30, 9, 3, 3)},
        };

        std::cout << "Welcome to the turn-based battle game.\n";
        std::cout << "\nChoose your opponent (ascending difficulty):\n";
        for (std::size_t i = 0; i < roster.size(); ++i) {
            std::cout << i + 1 << ". " << roster[i].name
                      << " -> " << roster[i].stats << "\n";
        }

        int pick = 0;
        while (true) {
            std::cout << "Enter choice: ";
            if (!(std::cin >> pick)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (pick < 1 || static_cast<std::size_t>(pick) > roster.size()) {
                std::cout << "Please choose a number between 1 and " << roster.size() << ".\n";
                continue;
            }
            break;
        }

        const EnemyDef& chosen = roster[pick - 1];
        std::cout << "\nYou chose to face the " << chosen.name << "!\n";

        Battle battle(hero);
        battle.addEnemy(std::make_unique<Enemy>(chosen.name, chosen.stats));
        battle.run();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
