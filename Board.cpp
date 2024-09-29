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
#include <iostream>
#include <map>

// Color definitions for different groups
const std::string RESET = "\033[0m";
const std::map<std::string, std::string> STREET_COLORS = {
    {"brown", "\033[38;5;94m"},
    {"Light Blue", "\033[38;5;117m"},
    {"pink", "\033[38;5;204m"},
    {"orange", "\033[38;5;214m"},
    {"red", "\033[38;5;196m"},
    {"yellow", "\033[38;5;226m"},
    {"green", "\033[38;5;46m"},
    {"blue", "\033[38;5;21m"}
};


Board::Board() {
    initializeSlots();
}

Slot* Board::getSlot(int position) const {
    return slots[position % slots.size()].get();  // Ensure the position wraps around the board size
}

void Board::initializeSlots() {
    // Add the slots in the correct order, starting with Go
    slots.push_back(std::make_unique<GoSlot>());  // Start slot
    
    // Brown properties
    slots.push_back(std::make_unique<Street>("Mediterranean Avenue", "brown", 60, 2, 50, 200));
    slots.push_back(std::make_unique<SurpriseSlot>());  // Chance or Community Chest
    slots.push_back(std::make_unique<Street>("Baltic Avenue", "brown", 60, 4, 50, 200));
    
    // Income Tax
    slots.push_back(std::make_unique<TaxSlot>(200));  // Tax slot

    // Train station
    slots.push_back(std::make_unique<TrainStation>(200));  // Reading Railroad
    
    // Light Blue properties
    slots.push_back(std::make_unique<Street>("Oriental Avenue", "Light Blue", 100, 6, 50, 300));
    slots.push_back(std::make_unique<SurpriseSlot>());  // Chance or Community Chest
    slots.push_back(std::make_unique<Street>("Vermont Avenue", "Light Blue", 100, 6, 50, 300));
    slots.push_back(std::make_unique<Street>("Connecticut Avenue", "Light Blue", 120, 8, 50, 300));
    
    // Jail
    slots.push_back(std::make_unique<JailSlot>());
    
    // Pink properties
    slots.push_back(std::make_unique<Street>("St. Charles Place", "pink", 140, 10, 100, 400));
    slots.push_back(std::make_unique<Utility>("Electric Company", 150));  // Utility
    slots.push_back(std::make_unique<Street>("States Avenue", "pink", 140, 10, 100, 400));
    slots.push_back(std::make_unique<Street>("Virginia Avenue", "pink", 160, 12, 100, 400));
    
    // Train station
    slots.push_back(std::make_unique<TrainStation>(200));  // Pennsylvania Railroad

    // Orange properties
    slots.push_back(std::make_unique<Street>("St. James Place", "orange", 180, 14, 100, 450));
    slots.push_back(std::make_unique<SurpriseSlot>());  // Chance or Community Chest
    slots.push_back(std::make_unique<Street>("Tennessee Avenue", "orange", 180, 14, 100, 450));
    slots.push_back(std::make_unique<Street>("New York Avenue", "orange", 200, 16, 100, 450));

    // Free Parking
    slots.push_back(std::make_unique<FreeParkingSlot>());
    
    // Red properties
    slots.push_back(std::make_unique<Street>("Kentucky Avenue", "red", 220, 18, 150, 500));
    slots.push_back(std::make_unique<SurpriseSlot>());  // Chance or Community Chest
    slots.push_back(std::make_unique<Street>("Indiana Avenue", "red", 220, 18, 150, 500));
    slots.push_back(std::make_unique<Street>("Illinois Avenue", "red", 240, 20, 150, 500));
    
    // Train station
    slots.push_back(std::make_unique<TrainStation>(200));  // B&O Railroad
    
    // Yellow properties
    slots.push_back(std::make_unique<Street>("Atlantic Avenue", "yellow", 260, 22, 150, 550));
    slots.push_back(std::make_unique<Street>("Ventnor Avenue", "yellow", 260, 22, 150, 550));
    slots.push_back(std::make_unique<Utility>("Water Works", 150));  // Utility
    slots.push_back(std::make_unique<Street>("Marvin Gardens", "yellow", 280, 24, 150, 550));
    
    // Go to Jail
    slots.push_back(std::make_unique<GoToJailSlot>());
    
    // Green properties
    slots.push_back(std::make_unique<Street>("Pacific Avenue", "green", 300, 26, 200, 600));
    slots.push_back(std::make_unique<Street>("North Carolina Avenue", "green", 300, 26, 200, 600));
    slots.push_back(std::make_unique<SurpriseSlot>());  // Chance or Community Chest
    slots.push_back(std::make_unique<Street>("Pennsylvania Avenue", "green", 320, 28, 200, 600));
    
    // Train station
    slots.push_back(std::make_unique<TrainStation>(200));  // Short Line Railroad
    
    // Blue properties
    slots.push_back(std::make_unique<Street>("Park Place", "blue", 350, 35, 200, 700));
    slots.push_back(std::make_unique<TaxSlot>(100));  // Luxury Tax
    slots.push_back(std::make_unique<Street>("Boardwalk", "blue", 400, 50, 200, 700));
}

void Board::display() const {
    std::cout << "Board Layout:\n";
    for (size_t i = 0; i < slots.size(); ++i) {
        std::cout << "Slot " << i << ": ";
        slots[i]->display();
    }
}

void Board::drawBoard(const std::vector<Player>& players) const {
    std::cout << "\n+--------+---------------------+--------------------+\n";
    std::cout << "| Slot # |       Property       |       Players      |\n";
    std::cout << "+--------+---------------------+--------------------+\n";

    // Iterate through all slots
    for (std::size_t i = 0; i < slots.size(); ++i) {
        printSlot(i, players);
    }

    std::cout << "+--------+---------------------+--------------------+\n";
}


void Board::printSlot(int index, const std::vector<Player>& players, bool vertical) const {
    Slot* slot = getSlot(index);
    std::string slotName = "Slot " + std::to_string(index);
    std::string ownerInfo = "";
    std::string playerMarkers;

    // Determine the slot type and apply coloring if it's a street
    if (Street* street = dynamic_cast<Street*>(slot)) {
        slotName = street->getName();
        std::string color = street->getColor();
        std::string colorCode = STREET_COLORS.at(color);

        // Check for ownership
        if (street->getOwner() != nullptr) {
            ownerInfo = " O(" + street->getOwner()->getName().substr(0, 1) + ")";
        }

        // Print the colored street with ownership indicator
        std::cout << "|   " << std::setw(3) << index << "   | "
                  << colorCode << std::setw(19) << slotName << RESET << ownerInfo << " ";
    } else if (dynamic_cast<GoSlot*>(slot)) {
        std::cout << "|   " << std::setw(3) << index << "   | " << std::setw(19) << "Go" << " ";
    } else if (dynamic_cast<JailSlot*>(slot)) {
        std::cout << "|   " << std::setw(3) << index << "   | " << std::setw(19) << "Jail" << " ";
    } else if (dynamic_cast<FreeParkingSlot*>(slot)) {
        std::cout << "|   " << std::setw(3) << index << "   | " << std::setw(19) << "Free Parking" << " ";
    } else if (dynamic_cast<TaxSlot*>(slot)) {
        std::cout << "|   " << std::setw(3) << index << "   | " << std::setw(19) << "Tax Slot" << " ";
    } else if (dynamic_cast<TrainStation*>(slot)) {
        std::cout << "|   " << std::setw(3) << index << "   | " << std::setw(19) << "Train Station" << " ";
    } else {
        std::cout << "|   " << std::setw(3) << index << "   | " << std::setw(19) << slotName << " ";
    }

    // Check for players on the slot and display their symbols
    for (const Player& player : players) {
        if (player.getPosition() == index) {
            playerMarkers += player.getSymbol();  // Use the player's symbol instead of initials
            playerMarkers += " ";
        }
    }

    std::cout << "| " << std::setw(18) << playerMarkers << "|\n";
}