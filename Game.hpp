#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <string>

class Game {
public:
    Game(int numPlayers, const std::vector<std::string>& playerSymbols);  // Updated constructor

    void start();
    void takeTurn(Player& player);
    bool isGameOver() const;
    void displayStatus() const;

    std::vector<Player>& getPlayers();  // New method to get players

private:
    std::vector<Player> players;
    Board board;
    int currentPlayerIndex;
    void setupPlayers(int numPlayers, const std::vector<std::string>& playerSymbols);
};

#endif
