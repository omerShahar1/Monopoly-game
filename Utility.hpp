#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Slot.hpp"
#include "Player.hpp"
#include <string>

class Utility : public Slot {
public:
    Utility(const std::string& name, int price); // 
    void performAction(Player& player) override;
    void display() const override;
    Player* getOwner() const;
    std::string getName() const;

private:
    std::string name;
    int price;
    Player* owner;
};

#endif



/*The Utility class in the Monopoly game represents the utility slots on the board 
(e.g., the Electric Company and Water Works). Utilities function differently from 
regular properties like streets or train stations. When a player lands on a utility 
that is owned by another player, the amount of rent they pay is determined by the roll of the dice, 
multiplied by a fixed amount.

Functions of the Utility Class:
* Constructor (Utility(const std::string& name, int price)): Initializes the utility with a name (e.g., "Electric Company") and its price.
* performAction(Player& player): Handles the actions when a player lands on the utility.
If the utility is unowned, the player can purchase it.
If another player owns it, the rent is determined by multiplying the dice roll result by a fixed rate (usually 10).
* getOwner(): Returns the player who owns the utility or nullptr if it is unowned.
* getName(): Returns the name of the utility (e.g., "Water Works" or "Electric Company").
* display(): Displays the details of the utility, such as its name and whether it is owned.

Summary:
The Utility class is designed to manage the special behavior of utility slots in Monopoly. When a player lands on a utility, 
rent is determined based on a dice roll rather than a fixed amount, making it different from regular streets and train stations. 
The class contains methods to manage ownership, calculate rent, and display utility information.*/