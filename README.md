# Turn-Based Battle Game (C++)

This project is a terminal-based turn-based battle game designed to fit a typical introductory/intermediate C++ final project assignment. It is intentionally small enough to understand, extend, and present in a concept demo video.

## What the game does
- Creates one player and several enemies
- Runs a turn-based combat loop
- Lets the user choose actions from a menu
- Ends when either the player or all enemies are defeated

## Files
- `include/Stats.hpp`, `src/Stats.cpp` - stats class and overloaded operators
- `include/Character.hpp`, `src/Character.cpp` - abstract base class
- `include/Player.hpp`, `src/Player.cpp` - derived player class
- `include/Enemy.hpp`, `src/Enemy.cpp` - derived enemy class
- `include/GameExceptions.hpp` - custom exception types
- `include/Battle.hpp`, `src/Battle.cpp` - battle loop and game logic
- `src/main.cpp` - program entry point
- `Makefile` - build/run/valgrind commands

## How to build
From the project folder:

```bash
make
```

## How to run
```bash
make run
```

You will see a menu like this during the game:
- `1` = attack an enemy
- `2` = inspect the strongest enemy

## How to run with valgrind
```bash
make valgrind
```

If everything is correct, valgrind should report:
- no invalid reads/writes
- no definitely lost memory

## The 6 assignment concepts this version demonstrates

### 1. Throwing and catching at least two types of exception (C)
**C++ perspective:**
- `InvalidChoiceException` inherits from `std::runtime_error`
- `BattleStateException` inherits from `std::logic_error`
- These are thrown in `Battle.cpp` and caught in the game loop

**Project perspective:**
- Invalid menu input is handled without crashing the game
- Invalid battle situations, like targeting a defeated enemy, are reported clearly

### 2. A class with access specifiers, at least one constructor, and a destructor (D)
**C++ perspective:**
- `Character`, `Battle`, and `Stats` all use private/protected/public sections
- Constructors initialize object state
- `Character` and `Battle` include destructors

**Project perspective:**
- These classes organize the game into manageable parts: stats, characters, and the battle system

### 3. At least 4 overloaded operators for a class you wrote (E)
**C++ perspective:**
The `Stats` class overloads:
- `operator+`
- `operator-`
- `operator==`
- `operator<`
- `operator<<` for printing

**Project perspective:**
- Stats can be compared, combined, and printed cleanly during gameplay and explanations

### 4. A class that uses inheritance and polymorphism, overriding at least one function (F)
**C++ perspective:**
- `Character` is an abstract base class
- `Player` and `Enemy` derive from it
- They override `computeDamage()` and `getRole()`

**Project perspective:**
- Player and enemies share common behavior but calculate damage differently

### 5. An STL container that is not a vector or string (J)
**C++ perspective:**
- `std::deque<std::unique_ptr<Character>> enemies`
- `std::map<int, std::string> commands`

**Project perspective:**
- The deque stores enemies in battle order
- The map stores menu options in a clean way

### 6. An STL algorithm with a functor or lambda function (K)
**C++ perspective:**
- `std::all_of(...)` uses a lambda to check whether all enemies are defeated
- `std::max_element(...)` uses a lambda to inspect the strongest enemy

**Project perspective:**
- This keeps the code shorter and more expressive than manual loops for those tasks

## Good next upgrades if you want a stronger final project
You can add any of these later:
- more enemy types using derived classes
- healing items
- random critical hits
- a save/load system
- unit tests with CxxTest
- debugger demo in VS Code
- callgrind analysis

## Suggested demo order for your presentation
1. Show the folder structure
2. Run `make`
3. Run `make run`
4. Play through one full battle
5. Run `make valgrind`
6. Explain the 6 concepts above
7. End with external resources / AI-use statement

## External resources statement template
You can say something like this in your presentation:

> I used course materials, online references, and AI tools for brainstorming, debugging help, and syntax support. Any generated code still required review, adjustment, and testing before I used it. I did not use any LLM or AI resource to create my video or concept demonstrations.
