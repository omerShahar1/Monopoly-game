#include "Player.hpp"
#include "Street.hpp"
#include <iostream>
#include <unordered_map>

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLUE = "\033[34m";

Player::Player(const std::string& name, const std::string& symbol)
    : name(name), symbol(symbol), money(1500), position(0) {}

std::string Player::getName() const {
    return name;
}

std::string Player::getSymbol() const {
    return symbol;
}

int Player::getPosition() const {
    return position;
}

void Player::setPosition(int newPosition) {
    position = newPosition;
}

void Player::move(int diceRoll) {
    if (!inJail()) {
        position = (position + diceRoll) % 40;
        std::cout << BLUE << "🚶 " << name << " moved to position " << position << "." << RESET << "\n";
    } else {
        std::cout << RED << "🚔 " << name << " is in jail and cannot move." << RESET << "\n";
    }
}

void Player::pay(int amount, Player* creditor) {
    money -= amount;
    std::cout << RED << name << " paid " << amount << " and now has $" << money << " left." << RESET << "\n";
    if (money < 0) {
        bankrupt = true;
        std::cout << RED << name << " is bankrupt!" << RESET << std::endl;
        handleBankruptcy(creditor);
    }
}

void Player::receive(int amount) {
    money += amount;
    std::cout << GREEN << name << " received $" << amount << " and now has $" << money << "." << RESET << "\n";
}

bool Player::isBankrupt() const {
    return bankrupt;
}

int Player::getMoney() const {
    return money;
}

void Player::addProperty(Slot* property) {
    properties.push_back(property);
    std::cout << GREEN << name << " acquired a new property." << RESET << "\n";

    if (Street* street = dynamic_cast<Street*>(property)) {
        const std::string& color = street->getColor();
        colorGroupCount[color]++;
    }
}

void Player::listProperties() const {
    std::cout << name << "'s properties:\n";
    if (properties.empty()) {
        std::cout << "No properties owned.\n";
    } else {
        for (const auto& property : properties) {
            property->display();
        }
    }
}

// Function to check if the player owns a full color set and offer to build a house
void Player::checkFullColorSetAndOfferBuild() 
{
    std::vector<std::string> colorGroups = {"blue", "brown", "Light Blue", "orange", "pink", "green", "yellow", "red"};
    for (std::string colorGroup : colorGroups) 
    {
    // Track the streets in the specified color group
    std::vector<Street*> colorGroupStreets;

    // Iterate over the player's properties
    for (Slot* property : properties) {
        Street* street = dynamic_cast<Street*>(property);
        if (street && street->getColor() == colorGroup) {
            colorGroupStreets.push_back(street);
        }
    }

    // Check if the player owns all streets in the color group
    int requiredCount = 0;
    if (colorGroup == "blue" || colorGroup == "brown" ) {
        requiredCount = 2;  // only 2 blue streets
    } else if (colorGroup == "Light Blue" || colorGroup == "orange" || colorGroup == "pink" || colorGroup == "green" || colorGroup == "yellow" || colorGroup == "red") {
        requiredCount = 3;  // 3 streets in these groups
    }

    // If the player owns the full set, offer to build houses
    if (colorGroupStreets.size() == requiredCount) {
        std::cout << "You own all " << colorGroup << " streets! Would you like to build a house? (y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') 
        {
            while(1)
            {
                for (Street* street : colorGroupStreets) 
                {
                    
                    if(street->get_hasHotel())
                    {
                        std::cout << "there is already a hotel in " << street->getName() << ".\n";
                        continue;
                    }
                    if (street->getHouses()) {
                        std::cout << "Building a house on " << street->getName() << ".\n";
                        street->buildHouse();
                    } 
                    else 
                    {
                            std::cout << "Building a hotel on " << street->getName() << ".\n";
                            street->buildHouse();
                    }
                }
                std::cout << "would you like to continue? (y/n):" << ".\n";
                std::cin >> choice;

                if (choice == 'n' || choice == 'N')
                {
                    break;
                }
            } 
        }
        else 
        {
            std::cout << "You chose not to build any houses.\n";
        }
    } 
    else 
    {
        std::cout << "You don't own the full " << colorGroup << " color set yet.\n";
    }
    }
}

bool Player::ownsAllPropertiesInColor(const std::string& color) const {
    std::unordered_map<std::string, int> colorGroupSizes = {
        {"brown", 2}, {"Light Blue", 3}, {"pink", 3},
        {"orange", 3}, {"red", 3}, {"yellow", 3},
        {"green", 3}, {"Purple", 2}
    };

    auto it = colorGroupSizes.find(color);
    if (it != colorGroupSizes.end()) {
        int requiredCount = it->second;
        return colorGroupCount.at(color) == requiredCount;
    }
    return false;
}

void Player::handleBankruptcy(Player* creditor = NULL) {
    if (creditor) {
        std::cout << name << " transfers all properties to " << creditor->getName() << "!\n";
        for (Slot* property : properties) {
            creditor->addProperty(property);
        }
        creditor->receive(money);
        properties.clear();
    } else {
        std::cout << name << " loses all properties to the bank.\n";
        properties.clear();
    }
}

void Player::goToJail() {
    jailStatus = true;
    turnsInJail = 0;
    std::cout << RED << name << " is sent to jail!" << RESET << "\n";
}

void Player::leaveJail() {
    jailStatus = false;
    turnsInJail = 0;
    std::cout << GREEN << name << " has left jail." << RESET << "\n";
}

bool Player::hasRolledDoubles(int dice1, int dice2) const {
    return dice1 == dice2;
}

void Player::attemptToLeaveJail() {
    turnsInJail++;

    if(out_of_jail_card > 0)
    {
        std::cout << "would you like to use get out of jail card? " << "? (y/n): " << "\n";
        char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') 
            {
                
                reduce_out_of_jail_card();
                leaveJail();
                std::cout << GREEN << name << " paid " << jailFee << " to leave jail." << RESET << "\n";
            }
    }

    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    if (hasRolledDoubles(dice1, dice2)) {
        leaveJail();
        std::cout << GREEN << name << " rolled doubles and left jail!" << RESET << "\n";
    } else if (turnsInJail >= 3) {
        if (money >= jailFee) {
            pay(jailFee);
            leaveJail();
            std::cout << GREEN << name << " paid " << jailFee << " to leave jail." << RESET << "\n";
        } else {
            bankrupt = true;
            handleBankruptcy();
            std::cout << RED << name << " cannot afford the jail fee and going bankrupt." << RESET << "\n";
        }
    } else {
        std::cout << RED << name << " did not roll doubles and remains in jail." << RESET << "\n";
        std::cout << "would you like to pay the fine? " << "? (y/n): " << "\n";
        char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                if (money >= jailFee) {
                    pay(jailFee);
                    leaveJail();
                    std::cout << GREEN << name << " paid " << jailFee << " to leave jail." << RESET << "\n";
                }
                else
                {
                    std::cout << RED << "❌ You don't have enough money!" << RESET << "\n";
                }
            }
    }
}

int Player::get_out_of_jail_card()
{
    return out_of_jail_card;
}
void Player::add_out_of_jail_card()
{
    out_of_jail_card++;
}
void Player::reduce_out_of_jail_card()
{
    out_of_jail_card--;
}

bool Player::inJail() const {
    return jailStatus;
}

int Player::get_trains_counter()
{
    return trains_counter;
}
void Player::add_train()
{
    trains_counter++;
}
