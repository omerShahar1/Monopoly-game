#include "Game.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Street.hpp"
#include <iostream>
#include <cassert>

#include "Game.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Street.hpp"
#include "TrainStation.hpp"
#include "Utility.hpp"
#include "JailSlot.hpp"
#include "GoSlot.hpp"
#include "SurpriseSlot.hpp"
#include "TaxSlot.hpp"
#include <iostream>
#include <cassert>

void testPlayerMovement() {
    Player player("TestPlayer", "♟");

    // Move player by rolling a 4
    player.move(4);
    assert(player.getPosition() == 4);
    
    // Move again and wrap around the board
    player.move(36);  // 40 slots in total, should wrap around
    assert(player.getPosition() == 0);
    
    std::cout << "testPlayerMovement passed.\n";
}

void testPropertyPurchase() {
    Player player1("Player1", "♟");
    Player player2("Player2", "♞");
    
    Street street("Park Place", "blue", 350, 35, 150, 200);

    // Player1 buys the property
    street.performAction(player1);
    assert(street.getOwner() == &player1);
    assert(player1.getMoney() == 1500 - 350);
    
    // Player2 lands on the property and pays rent
    int previousMoney = player2.getMoney();
    street.performAction(player2);
    assert(player2.getMoney() == previousMoney - 35);  // Rent payment
    assert(player1.getMoney() == 1500 - 350 + 35);  // Player1 receives rent
    
    std::cout << "testPropertyPurchase passed.\n";
}

void testHouseBuilding() {
    Player player1("Player1", "♟");
    
    Street street1("Park Place", "blue", 350, 35, 150, 200);
    Street street2("Boardwalk", "blue", 400, 50, 200, 250);

    // Simulate player owning both streets in the color group
    street1.performAction(player1);
    street2.performAction(player1);

    // Player builds houses
    street1.buildHouse();
    street2.buildHouse();
    assert(street1.getHouses() == 1);
    assert(street2.getHouses() == 1);
    
    std::cout << "testHouseBuilding passed.\n";
}

void testPassingGo() {
    Player player1("Player1", "♟");
    
    player1.move(39);  // Move player close to "Go"
    player1.move(2);   // Player moves past "Go"
    assert(player1.getMoney() == 1700);  // Should collect $200
    
    std::cout << "testPassingGo passed.\n";
}

void testJailMechanism() {
    Player player1("Player1", "♟");
    Board board;

    // Simulate landing on "Go to Jail" slot
    player1.setPosition(30);
    board.getSlot(30)->performAction(player1);
    assert(player1.getPosition() == 10);  // Player is in jail

    // Simulate player paying the jail fee to get out
    player1.pay(50);
    player1.setPosition(11);  // Player moves out of jail
    assert(player1.getMoney() == 1450);  // Deduct $50
    
    std::cout << "testJailMechanism passed.\n";
}

void testRentWithHouses() {
    Player player1("Player1", "♟");
    Player player2("Player2", "♞");
    
    Street street("Park Place", "blue", 350, 35, 150, 200);

    // Player1 buys the property
    street.performAction(player1);

    // Player1 builds houses
    street.buildHouse();
    street.buildHouse();

    // Player2 lands on the property and pays rent (with houses)
    int previousMoney = player2.getMoney();
    street.performAction(player2);
    assert(player2.getMoney() == previousMoney - (35 * 2));  // Rent doubled with 2 houses
    
    std::cout << "testRentWithHouses passed.\n";
}

void testSurpriseSlot() {
    Player player1("Player1", "♟");
    Board board;
    
    // Simulate landing on a surprise slot
    board.getSlot(7)->performAction(player1);  // Assuming slot 7 is a surprise slot
    
    // The surprise slot behavior should apply (e.g., get out of jail free, money bonus, etc.)
    // For now, we just assume a bonus is given; actual behavior depends on your implementation.
    // For example, check if money increased if a bonus was given:
    assert(player1.getMoney() >= 1500);  // Assuming the player was awarded some money
    
    std::cout << "testSurpriseSlot passed.\n";
}

void testGameOver() {
    // Prepare symbols for the players
    std::vector<std::string> playerSymbols = {"♟", "♞"};

    // Initialize the game with 2 players
    Game game(2, playerSymbols);

    // Simulate player bankruptcy by manually reducing the player's money
    Player& player1 = game.getPlayers()[0];
    Player& player2 = game.getPlayers()[1];

    // Make player1 bankrupt
    player1.pay(player1.getMoney());

    // Run the game loop
    game.start();

    // After the game loop, check if player1 is removed and the game is over
    assert(game.isGameOver());

    std::cout << "testGameOver passed.\n";
}


// Test for Player class
void testPlayerMovement() {
    Player player("TestPlayer", "♟");

    // Move player by rolling a 4
    player.move(4);
    assert(player.getPosition() == 4);
    
    // Move again and wrap around the board
    player.move(36);  // 40 slots in total, should wrap around
    assert(player.getPosition() == 0);
    
    std::cout << "testPlayerMovement passed.\n";
}

void testPlayerPayment() {
    Player player1("Player1", "♟");
    Player player2("Player2", "♞");

    // Player1 pays Player2
    player1.pay(50, &player2);
    assert(player1.getMoney() == 1450);
    assert(player2.getMoney() == 1550);

    // Player1 becomes bankrupt
    player1.pay(1450);
    assert(player1.isBankrupt() == true);

    std::cout << "testPlayerPayment passed.\n";
}

void testFullColorSetAndBuild() {
    Player player("TestPlayer", "♟");
    Street street1("Park Place", "blue", 350, 35, 150, 200);
    Street street2("Boardwalk", "blue", 400, 50, 200, 250);

    // Player buys the streets
    street1.performAction(player);
    street2.performAction(player);

    // Now check if the player can build houses (owns all blue streets)
    player.checkFullColorSetAndOfferBuild();
    assert(street1.getHouses() == 1);
    assert(street2.getHouses() == 1);

    std::cout << "testFullColorSetAndBuild passed.\n";
}

// Test for Street class
void testStreetPurchaseAndRent() {
    Player player1("Player1", "♟");
    Player player2("Player2", "♞");

    Street street("Park Place", "blue", 350, 35, 150, 200);

    // Player1 buys the property
    street.performAction(player1);
    assert(street.getOwner() == &player1);
    assert(player1.getMoney() == 1150);

    // Player2 lands on the property and pays rent
    int previousMoney = player2.getMoney();
    street.performAction(player2);
    assert(player2.getMoney() == previousMoney - 35);  // Rent payment
    assert(player1.getMoney() == 1150 + 35);  // Player1 receives rent

    std::cout << "testStreetPurchaseAndRent passed.\n";
}

// Test for TrainStation class
void testTrainStation() {
    Player player1("Player1", "♟");
    Player player2("Player2", "♞");

    TrainStation station(200);

    // Player1 buys the station
    station.performAction(player1);
    assert(station.getOwner() == &player1);
    assert(player1.getMoney() == 1300);  // Paid 200 for the station

    // Player2 lands on the station and pays rent
    station.performAction(player2);
    assert(player2.getMoney() == 1500 - 50);  // 50 for one station
    assert(player1.getMoney() == 1300 + 50);  // Player1 receives rent

    std::cout << "testTrainStation passed.\n";
}

// Test for Utility class
void testUtility() {
    Player player1("Player1", "♟");
    Player player2("Player2", "♞");

    Utility utility("Electric Company", 150);

    // Player1 buys the utility
    utility.performAction(player1);
    assert(utility.getOwner() == &player1);
    assert(player1.getMoney() == 1350);  // Paid 150 for utility

    // Player2 lands on the utility, rolls 7, pays 70
    int diceRoll = 7;
    player2.move(diceRoll);
    utility.performAction(player2);
    assert(player2.getMoney() == 1500 - 70);  // 10 * dice roll
    assert(player1.getMoney() == 1350 + 70);  // Player1 receives rent

    std::cout << "testUtility passed.\n";
}

// Test for Board and Special Slots
void testSpecialSlots() {
    Player player1("Player1", "♟");
    Board board;

    // Go slot
    Slot* goSlot = board.getSlot(0);
    goSlot->performAction(player1);
    assert(player1.getMoney() == 1700);  // Passed Go, collect $200

    // Go to Jail slot
    Slot* goToJailSlot = board.getSlot(30);
    goToJailSlot->performAction(player1);
    assert(player1.getPosition() == 10);  // Player goes to jail

    // Free Parking
    Slot* freeParkingSlot = board.getSlot(20);
    freeParkingSlot->performAction(player1);  // Nothing happens

    std::cout << "testSpecialSlots passed.\n";
}

// Test for Game class
void testGameOver() {
    std::vector<std::string> playerSymbols = {"♟", "♞"};
    Game game(2, playerSymbols);

    // Simulate one player becoming bankrupt
    Player& player1 = game.getPlayers()[0];
    player1.pay(player1.getMoney());

    game.start();

    // Check if the game ends
    assert(game.isGameOver());

    std::cout << "testGameOver passed.\n";
}

// Main function to run all tests
int main() {

    return 0;
}


int main() {
    testPlayerMovement();
    testPropertyPurchase();
    testHouseBuilding();
    testPassingGo();
    testJailMechanism();
    testRentWithHouses();
    testSurpriseSlot();
    testGameOver();
    testPlayerPayment();
    testFullColorSetAndBuild();
    testStreetPurchaseAndRent();
    testTrainStation();
    testUtility();
    testSpecialSlots();
    testGameOver();
    
    std::cout << "All tests passed!\n";
    
    std::cout << "All tests passed!\n";
    return 0;
}
