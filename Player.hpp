#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "Slot.hpp"

class Player {
public:
    Player(const std::string& name, const std::string& symbol);

    std::string getSymbol() const;  // New method to get the player's symbol
    void move(int diceRoll);            
    void pay(int amount, Player* creditor = nullptr);  
    void receive(int amount);           
    bool isBankrupt() const;            
    int getMoney() const;               
    void addProperty(Slot* property);   
    void listProperties() const;        
    bool ownsAllPropertiesInColor(const std::string& color) const;
    void checkFullColorSetAndOfferBuild();

    std::string getName() const;        
    int getPosition() const;            
    void setPosition(int newPosition);  

    void goToJail();
    void leaveJail();
    void attemptToLeaveJail();
    bool inJail() const;
    bool hasRolledDoubles(int dice1, int dice2) const;
    int get_out_of_jail_card();
    void add_out_of_jail_card();
    void reduce_out_of_jail_card();
    int get_trains_counter();
    void add_train();


private:
    std::string name;
    std::string symbol;  // New symbol attribute
    int money;
    int position;
    std::vector<Slot*> properties;
    bool bankrupt;

    std::unordered_map<std::string, int> colorGroupCount;
    bool jailStatus;
    int turnsInJail;
    int trains_counter=0;
    static const int jailFee = 50;
    int out_of_jail_card = 0;

    void handleBankruptcy(Player* creditor);
};

#endif
