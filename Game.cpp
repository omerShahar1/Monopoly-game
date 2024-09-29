#include "Game.hpp"
#include <iostream>
#include <limits>  // For std::numeric_limits

Game::Game(int numPlayers, const std::vector<std::string>& playerSymbols)
    : currentPlayerIndex(0) {
    setupPlayers(numPlayers, playerSymbols);
}

void Game::setupPlayers(int numPlayers, const std::vector<std::string>& playerSymbols) {
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Enter name for Player " << (i + 1) << ": ";
        std::getline(std::cin, name);
        players.emplace_back(name, playerSymbols[i]);
    }
}

void Game::start() {
    while (!isGameOver()) {
        Player& currentPlayer = players[currentPlayerIndex];
        if (currentPlayer.isBankrupt()) {
            std::cout << currentPlayer.getName() << " is bankrupt and removed from the game.\n";
            players.erase(players.begin() + currentPlayerIndex);
            if (players.empty()) {
                std::cout << "All players are bankrupt. The game is over.\n";
                return;
            }
        } else {
            takeTurn(currentPlayer);
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
    }
}

void Game::takeTurn(Player& player) {
    std::cout << "\n" << player.getName() << "'s TURN\n";
    std::cout << player.getName() << ", press Enter to ROLL the dice...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int diceRoll = (rand() % 6 + 1) + (rand() % 6 + 1);
    std::cout << "\n" << player.getName() << " rolled a " << diceRoll << "!\n";
    
    player.move(diceRoll);
    Slot* slot = board.getSlot(player.getPosition());
    slot->performAction(player);

    board.drawBoard(players);
}

bool Game::isGameOver() const {
    return players.size() == 1;
}

void Game::displayStatus() const {
    std::cout << "Game Status:\n";
    for (const Player& player : players) {
        std::cout << player.getName() << " has $" << player.getMoney() << "\n";
    }
    board.display();
}

// New method to return the list of players
std::vector<Player>& Game::getPlayers() {
    return players;
}
