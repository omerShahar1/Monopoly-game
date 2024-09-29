#include "Game.hpp"
#include <vector>
#include <iostream>

int main() {
    int numPlayers;
    std::cout << "Welcome to Monopoly!\n";
    std::cout << "Enter the number of players (2-8): ";
    std::cin >> numPlayers;
    std::cin.ignore();  // Ignore the newline character after entering the number of players

    // Define player symbols
    std::vector<std::string> playerSymbols = {"♟", "♞", "♖", "♜", "♝", "♛", "♕", "♔"};

    // Initialize the game with player count and their symbols
    Game game(numPlayers, playerSymbols);
    game.start();

    return 0;
}
