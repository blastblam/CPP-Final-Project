#ifndef GAME_EXCEPTIONS_HPP
#define GAME_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class InvalidChoiceException : public std::runtime_error {
public:
    explicit InvalidChoiceException(const std::string& message)
        : std::runtime_error(message) {}
};

class BattleStateException : public std::logic_error {
public:
    explicit BattleStateException(const std::string& message)
        : std::logic_error(message) {}
};

#endif
