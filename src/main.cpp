#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "Battle.hpp"
#include "Dragon.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Stats.hpp"

int main() {
    try {
        Player hero("Arin", Stats(45, 12, 4, 7));

        // Enemies listed in ascending order of strength
        struct EnemyDef { const char* name; Stats stats; };
        std::vector<EnemyDef> roster = {
            {"Slime",  Stats(25,  9, 2, 3)},
            {"Goblin", Stats(35, 12, 3, 4)},
            {"Orc",    Stats(55, 17, 6, 3)},
        };

        std::cout << "Welcome to the turn-based battle game.\n";
        std::cout << "\nChoose your opponent (ascending difficulty):\n";
        for (std::size_t i = 0; i < roster.size(); ++i) {
            std::cout << i + 1 << ". " << roster[i].name
                      << " -> " << roster[i].stats << "\n";
        }
        Dragon bossPreview;
        std::cout << roster.size() + 1 << ". [BOSS] " << bossPreview.getName()
                  << " -> " << bossPreview.getStats() << "\n";

        int pick = 0;
        while (true) {
            std::cout << "Enter choice: ";
            if (!(std::cin >> pick)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (pick < 1 || static_cast<std::size_t>(pick) > roster.size() + 1) {
                std::cout << "Please choose a number between 1 and " << roster.size() + 1 << ".\n";
                continue;
            }
            break;
        }

        bool dragonPick = (static_cast<std::size_t>(pick) == roster.size() + 1);
        std::size_t startIndex = dragonPick ? roster.size() : static_cast<std::size_t>(pick - 1);

        if (dragonPick) {
            std::cout << "\nYou chose to face the Dragon! Good luck...\n";
        } else {
            std::cout << "\nStarting from " << roster[startIndex].name << "!\n";
        }

        Battle battle(hero);
        // Add all enemies from chosen starting point onward
        for (std::size_t i = startIndex; i < roster.size(); ++i) {
            battle.addEnemy(std::make_unique<Enemy>(roster[i].name, roster[i].stats));
        }
        battle.addEnemy(std::make_unique<Dragon>());

        battle.run();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
