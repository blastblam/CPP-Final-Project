#include "Battle.hpp"

#include <algorithm>
#include <iostream>
#include <limits>

Battle::Battle(const Player& player)
    : player(player), healUsesLeft(2) {
    commands[1] = "Attack";
    commands[2] = "Inspect strongest living enemy";
    commands[3] = "Heal (2 uses remaining)";
}

Battle::~Battle() = default;

void Battle::addEnemy(std::unique_ptr<Character> enemy) {
    if (!enemy) {
        throw BattleStateException("Tried to add a null enemy.");
    }
    enemies.push_back(std::move(enemy));
}

bool Battle::allEnemiesDefeated() const {
    return std::all_of(enemies.begin(), enemies.end(), [](const std::unique_ptr<Character>& enemy) {
        return !enemy->isAlive();
    });
}

int Battle::calculateFinalDamage(const Character& attacker, const Character& defender) const {
    int base = attacker.computeDamage();
    int reduced = base - defender.getStats().getDefense();
    return reduced < 1 ? 1 : reduced;
}

void Battle::printStatus() const {
    std::cout << "\n===== BATTLE STATUS =====\n";
    std::cout << player.getName() << " (" << player.getRole() << ") -> " << player.getStats() << "\n";

    for (std::size_t i = 0; i < enemies.size(); ++i) {
        std::cout << i + 1 << ". " << enemies[i]->getName() << " (" << enemies[i]->getRole() << ") -> "
                  << enemies[i]->getStats();
        if (!enemies[i]->isAlive()) {
            std::cout << " [DEFEATED]";
        }
        std::cout << "\n";
    }
    std::cout << "=========================\n";
}

int Battle::chooseEnemyTarget() const {
    int target = 0;
    std::cout << "Choose enemy number to attack: ";
    if (!(std::cin >> target)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidChoiceException("Input was not a number.");
    }

    if (target < 1 || static_cast<std::size_t>(target) > enemies.size()) {
        throw InvalidChoiceException("That enemy number does not exist.");
    }

    if (!enemies[target - 1]->isAlive()) {
        throw BattleStateException("That enemy has already been defeated.");
    }

    return target - 1;
}

void Battle::playerTurn() {
    int choice = 0;
    commands[3] = "Heal (" + std::to_string(healUsesLeft) + " use" + (healUsesLeft == 1 ? "" : "s") + " remaining)";

    std::cout << "\nYour turn:\n";
    for (const auto& entry : commands) {
        std::cout << entry.first << ". " << entry.second << "\n";
    }
    std::cout << "Enter choice: ";

    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidChoiceException("Menu choice must be a number.");
    }

    if (choice == 1) {
        int targetIndex = chooseEnemyTarget();
        int damage = calculateFinalDamage(player, *enemies[targetIndex]);
        enemies[targetIndex]->takeDamage(damage);
        std::cout << player.getName() << " hits " << enemies[targetIndex]->getName()
                  << " for " << damage << " damage.\n";
    } else if (choice == 2) {
        auto strongest = std::max_element(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Character>& left, const std::unique_ptr<Character>& right) {
                return left->getStats() < right->getStats();
            });

        if (strongest == enemies.end()) {
            throw BattleStateException("No enemies are loaded into the battle.");
        }

        std::cout << "Strongest enemy by combined stats: "
                  << (*strongest)->getName() << " -> " << (*strongest)->getStats() << "\n";
    } else if (choice == 3) {
        if (healUsesLeft <= 0) {
            throw InvalidChoiceException("You have no heals remaining.");
        }
        player.heal(8);
        --healUsesLeft;
        std::cout << player.getName() << " heals for 8 HP. (" << healUsesLeft << " heal"
                  << (healUsesLeft == 1 ? "" : "s") << " remaining)\n";
    } else {
        throw InvalidChoiceException("That menu option is invalid.");
    }
}

void Battle::enemyTurn() {
    for (const auto& enemy : enemies) {
        if (!enemy->isAlive() || !player.isAlive()) {
            continue;
        }
        int damage = calculateFinalDamage(*enemy, player);
        player.takeDamage(damage);
        std::cout << enemy->getName() << " attacks " << player.getName()
                  << " for " << damage << " damage.\n";
    }
}

void Battle::run() {
    if (enemies.empty()) {
        throw BattleStateException("Cannot start a battle with no enemies.");
    }

    while (player.isAlive() && !allEnemiesDefeated()) {
        printStatus();
        try {
            playerTurn();
        } catch (const InvalidChoiceException& ex) {
            std::cout << "Invalid choice: " << ex.what() << "\n";
        } catch (const BattleStateException& ex) {
            std::cout << "Battle state error: " << ex.what() << "\n";
        }

        if (allEnemiesDefeated() || !player.isAlive()) {
            break;
        }

        enemyTurn();
    }

    printStatus();
    if (player.isAlive()) {
        std::cout << "\nYou won the battle.\n";
    } else {
        std::cout << "\nYou were defeated.\n";
    }
}
