#include "Board.hpp"
#include "Street.hpp"
#include "TrainStation.hpp"
#include "Utility.hpp"
#include "SurpriseSlot.hpp"
#include "JailSlot.hpp"
#include "TaxSlot.hpp"
#include "FreeParkingSlot.hpp"
#include "GoToJailSlot.hpp"
#include "GoSlot.hpp"
#include <iomanip>  // Include for std::setw
#include <map>

#include "Game.hpp"
#include "Player.hpp"
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
            else if(players.size() == 1)
            {
                std::string name = players.at(0).getName();
                std::cout << name << "is the winner! game over.\n";
                return;
            }
            for(size_t i=0; i<players.size(); i++)
            {
                if(players.at(i).getMoney() >= 4000)
                {
                    std::string name = players.at(0).getName();
                    std::cout << name << "is the winner! game over.\n";
                    return;
                }
            }
        } 
        else 
        {
            takeTurn(currentPlayer);
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
    }
}

void Game::takeTurn(Player& player) 
{
    
    if (player.inJail())
    {
        player.attemptToLeaveJail();
        if(player.inJail())
        {
            return;
        }
    }
    
    bool double_check = true;
    int double_counter = 0;
    while(double_check == true)
    {
        board.drawBoard(players);
        std::cout << "\n" << player.getName() << "'s TURN\n";
        std::cout << player.getName() << ", press Enter to ROLL the dice...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int diceRoll = dice1 + dice2;
        std::cout << "\n" << player.getName() << " rolled a " << dice1 << ", " << dice2 << "!\n";

        if(dice1 == dice2)
        {
            double_counter++;
            double_check = true;
        }
        else
        {
            double_check = false;
        }

        if(double_counter == 3)
        {
            player.goToJail();
            return;
        }
        
        player.move(diceRoll);
        Slot* slot = board.getSlot(player.getPosition());
        slot->performAction(player);
        
        displayStatus();


        std::cout << "\n\nwould you like to build houses? (y/n): \n ";
        char choice;
        std::cin >> choice;
        if(choice == 'y' || choice == 'Y')
        {
            player.checkFullColorSetAndOfferBuild();
        }

    }

    std::cout << "+--------+---------------------+--------------------+\n";
    std::cout << "+--------+---------------------+--------------------+\n";
    std::cout << "+--------+---------------------+--------------------+\n";
    std::cout << "+--------+---------------------+--------------------+\n";

    
}

bool Game::isGameOver() const {
    return players.size() == 1;
}

void Game::displayStatus() const {
    std::cout << "Game Status:\n";
    for (const Player& player : players) {
        std::cout << player.getName() << " has $" << player.getMoney() << "\n";
    }
    //board.display();
}

// New method to return the list of players
std::vector<Player>& Game::getPlayers() {
    return players;
}
