#include "Battle.hpp"

#include <algorithm>
#include <iostream>
#include <limits>

Battle::Battle(const Player& player)
    : player(player), healUsesLeft(2), currentEnemyIndex(0), defendTurnsLeft(0) {
    commands[1] = "Attack";
    commands[2] = "Defend (doubles DEF for 3 turns)";
    commands[3] = "Heal (2 uses remaining)";
}

Battle::~Battle() = default;

void Battle::addEnemy(std::unique_ptr<Character> enemy) {
    if (!enemy) {
        throw BattleStateException("Tried to add a null enemy.");
    }
    enemies.push_back(std::move(enemy));
}

bool Battle::promptContinue() const {
    char ans = 0;
    while (true) {
        std::cout << "\nContinue to the next enemy? (y/n): ";
        if (!(std::cin >> ans)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (ans == 'y' || ans == 'Y') return true;
        if (ans == 'n' || ans == 'N') return false;
    }
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
        } else if (i == currentEnemyIndex) {
            std::cout << " [CURRENT]";
        } else {
            std::cout << " [NEXT]";
        }
        std::cout << "\n";
    }
    std::cout << "=========================\n";
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
        Character& target = *enemies[currentEnemyIndex];
        int damage = calculateFinalDamage(player, target);
        target.takeDamage(damage);
        std::cout << player.getName() << " hits " << target.getName()
                  << " for " << damage << " damage.\n";
    } else if (choice == 2) {
        defendTurnsLeft = 3;
        std::cout << player.getName() << " takes a defensive stance! DEF doubled for 3 turns.\n";
    } else if (choice == 3) {
        if (healUsesLeft <= 0) {
            throw InvalidChoiceException("You have no heals remaining.");
        }
        int healAmount = static_cast<int>(player.getStats().getMaxHp() * 0.33);
        player.heal(healAmount);
        --healUsesLeft;
        std::cout << player.getName() << " heals for " << healAmount << " HP. ("
                  << healUsesLeft << " heal" << (healUsesLeft == 1 ? "" : "s") << " remaining)\n";
    } else {
        throw InvalidChoiceException("That menu option is invalid.");
    }
}

void Battle::enemyTurn() {
    Character& enemy = *enemies[currentEnemyIndex];
    int base = enemy.computeDamage();
    bool defending = defendTurnsLeft > 0;
    int defense = player.getStats().getDefense() * (defending ? 2 : 1);
    int damage = std::max(1, base - defense);
    player.takeDamage(damage);
    if (defending) {
        --defendTurnsLeft;
        std::cout << enemy.getName() << " attacks " << player.getName()
                  << " for " << damage << " damage (defended! " << defendTurnsLeft << " turn"
                  << (defendTurnsLeft == 1 ? "" : "s") << " remaining).\n";
    } else {
        std::cout << enemy.getName() << " attacks " << player.getName()
                  << " for " << damage << " damage.\n";
    }
}

void Battle::run() {
    if (enemies.empty()) {
        throw BattleStateException("Cannot start a battle with no enemies.");
    }

    while (player.isAlive() && currentEnemyIndex < enemies.size()) {
        // Fight the current enemy
        while (player.isAlive() && enemies[currentEnemyIndex]->isAlive()) {
            printStatus();
            try {
                playerTurn();
            } catch (const InvalidChoiceException& ex) {
                std::cout << "Invalid choice: " << ex.what() << "\n";
            } catch (const BattleStateException& ex) {
                std::cout << "Battle state error: " << ex.what() << "\n";
            }

            if (!enemies[currentEnemyIndex]->isAlive() || !player.isAlive()) break;
            enemyTurn();
        }

        if (!player.isAlive()) break;

        std::cout << "\n" << enemies[currentEnemyIndex]->getName() << " has been defeated!\n";

        if (enemies[currentEnemyIndex]->getRole() != "Boss") {
            int oldHp  = player.getStats().getHp();
            int oldAtk = player.getStats().getAttack();
            int oldDef = player.getStats().getDefense();
            player.gainStats(9, 2, 2, 70, 18, 8);
            std::cout << "Victory bonus! HP fully restored."
                      << "  HP: "  << oldHp  << " -> " << player.getStats().getHp()
                      << "  ATK: " << oldAtk << " -> " << player.getStats().getAttack()
                      << "  DEF: " << oldDef << " -> " << player.getStats().getDefense() << "\n";
        }

        ++currentEnemyIndex;

        if (currentEnemyIndex >= enemies.size()) break;

        if (!promptContinue()) {
            printStatus();
            std::cout << "\nYou withdrew from battle.\n";
            return;
        }
    }

    printStatus();
    if (!player.isAlive()) {
        std::cout << "\nYou were defeated.\n";
    } else {
        std::cout << "\nYou defeated all enemies!\n";
    }
}
