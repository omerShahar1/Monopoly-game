#ifndef TRAINSTATION_HPP
#define TRAINSTATION_HPP

#include "Slot.hpp"
#include "Player.hpp"

class TrainStation : public Slot {
public:
    TrainStation(int price);
    void performAction(Player& player) override;
    void display() const override;
    Player* getOwner() const;

private:
    int price;
    Player* owner;
};

#endif



/*The TrainStation class in the Monopoly game represents the four train station slots on the board. 
Unlike regular streets, rent for train stations increases based on how many stations the owning player possesses. 
If a player lands on an owned train station, they must pay rent, which scales with the number of train stations the owner owns.

Functions of the TrainStation Class:
* Constructor (TrainStation(const std::string& name, int price)): Initializes the train station with a name (e.g., "Reading Railroad") 
and its purchase price.
* performAction(Player& player): Handles the action when a player lands on the train station. If the station is unowned, the player can buy it.
If another player owns it, the rent is calculated based on how many train stations the owner possesses. The more stations owned, the higher the rent:
1 station: 50 units
2 stations: 100 units
3 stations: 150 units
4 stations: 200 units
* getOwner(): Returns the player who owns the train station or nullptr if it is unowned.
* getName(): Returns the name of the train station (e.g., "Reading Railroad", "Pennsylvania Railroad").
* display(): Displays the details of the train station, such as its name, price, and ownership status.


Summary:
The TrainStation class is used to represent the train stations on the Monopoly board. Rent increases as the owning player acquires more stations, making it more valuable than regular streets. The class manages ownership, calculates rent based on the number of stations owned, and provides a way to display the train station's information.*/
