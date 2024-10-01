#include "TrainStation.hpp"
#include <iostream>

const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

TrainStation::TrainStation(int price) : price(price), owner(nullptr) {}

void TrainStation::performAction(Player& player) {
    if (owner == nullptr) {
        if (player.getMoney() >= price) {
            std::cout << GREEN << "🚆 " << player.getName() << " landed on an available Train Station (Price: $" << price << ")." << RESET << "\n";
            std::cout << "Would you like to " << GREEN << "PURCHASE" << RESET << " this train station for $" << price << "? (y/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                player.pay(price);
                owner = &player;
                std::cout << GREEN << player.getName() << " bought the Train Station!" << RESET << "\n";
                player.add_train();
                player.addProperty(this);
            }
        } else {
            std::cout << RED << "❌ You don't have enough money to buy this train station!" << RESET << "\n";
        }
    } else if (owner != &player) {
        int rentDue = 50;  // Basic rent for one train station
        std::cout << RED << player.getName() << " landed on " << owner->getName() << "'s train station and must pay rent of $" << owner->get_trains_counter() * rentDue << "." << RESET << "\n";
        player.pay(owner->get_trains_counter() * rentDue, owner);
    } else {
        std::cout << GREEN << player.getName() << " landed on their own train station." << RESET << "\n";
    }
}

void TrainStation::display() const {
    if (owner) {
        std::cout << "🚆 Train Station - Owned by " << owner->getName() << ", Price: $" << price << "\n";
    } else {
        std::cout << "🚆 Train Station - Price: $" << price << "\n";
    }
}

Player* TrainStation::getOwner() const {
    return owner;
}
