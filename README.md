# Monopoly Game - C++ Implementation

This is a simple console-based implementation of the Monopoly board game, written in C++. The game allows 2-8 players to play on the same computer, each controlling a piece on the Monopoly board. Players can buy properties, build houses and hotels, and pay rent. The game continues until one player is left or someone wins with a balance of at least 4000 units.

## Table of Contents
- [Game Rules](#game-rules)
- [How to Play](#how-to-play)
- [Classes and Objects](#classes-and-objects)
- [Compiling and Running the Game](#compiling-and-running-the-game)
- [Testing the Game](#testing-the-game)
- [Future Improvements](#future-improvements)

## Game Rules

1. The game consists of a board with 40 slots. Each slot represents a street, train station, utility, or special action slot.
2. Players roll two dice and move around the board based on the dice result.
3. When a player lands on a street, they can purchase it if it is unowned. If another player owns the street, rent must be paid.
4. Players can build houses and hotels on their streets once they own all streets of a particular color group. 
   - The rent increases with each house, and the rent for a hotel is the highest.
5. Special slots include:
   - **Go**: Players collect $200 when they pass or land on "Go".
   - **Jail**: Players can go to jail by landing on the "Go to Jail" slot or by rolling doubles three times in a row.
   - **Surprise**: These slots provide random events such as bonuses, fines, or special cards.
6. Players can go bankrupt if they cannot afford to pay rent or taxes. Bankrupt players are removed from the game.
7. The game ends when only one player remains or a player achieves a balance of 4000 units.

## How to Play

1. At the start of the game, enter the number of players (2 to 8) and assign names.
2. Each player will take turns rolling two dice and moving around the board.
3. If a player lands on an unowned property, they can buy it. If they land on an owned property, they must pay rent.
4. Players can build houses and hotels on properties they own, increasing the rent other players must pay.
5. The game ends when one player is left or a player has a balance of 4000 units.

## Classes and Objects

### 1. **Game Class**
   - **Responsibilities**: Manages the flow of the game, including turns, dice rolls, and game over conditions.
   - **Key Methods**:
     - `start()`: Begins the game and controls the game loop.
     - `takeTurn(Player& player)`: Handles the player's turn, dice roll, and actions based on the slot they land on.
     - `isGameOver()`: Checks whether the game has ended.
     - `getPlayers()`: Returns a reference to the list of players in the game.

### 2. **Player Class**
   - **Responsibilities**: Represents a player in the game, managing their name, position on the board, money, and properties.
   - **Key Methods**:
     - `move(int diceRoll)`: Moves the player around the board based on the dice roll.
     - `pay(int amount, Player* creditor)`: Handles paying money to another player or the bank.
     - `isBankrupt()`: Checks whether the player is bankrupt.
     - `getPosition()`: Returns the player's current position on the board.

### 3. **Board Class**
   - **Responsibilities**: Manages the Monopoly board, consisting of 40 slots.
   - **Key Methods**:
     - `getSlot(int position)`: Returns the slot at the given position on the board.
     - `drawBoard(const std::vector<Player>& players)`: Draws a visual representation of the board in the console.

### 4. **Slot Class**
   - **Responsibilities**: Represents a generic slot on the board.
   - **Key Methods**:
     - `performAction(Player& player)`: A virtual function that each specific slot implements to define the action that happens when a player lands on it.

### 5. **Street Class (Derived from Slot)**
   - **Responsibilities**: Represents a street property on the board. Players can buy streets, build houses/hotels, and charge rent to others.
   - **Key Methods**:
     - `buildHouse()`: Allows the player to build houses on the street if they own it.
     - `performAction(Player& player)`: Handles buying the property or paying rent when a player lands on it.
     - `getHouses()`: Returns the number of houses on the street.

### 6. **Special Slot Classes**
   - **TaxSlot**: Deducts a certain amount of money from the player when they land on it.
   - **GoToJailSlot**: Sends the player to jail.
   - **FreeParkingSlot**: No action is taken when the player lands on this slot.
   - **SurpriseSlot**: Implements random events that can affect the player (e.g., get out of jail free card, money bonus, etc.).

### 7. **Utility and TrainStation Classes**
   - **Responsibilities**: Represent special slots for utilities (electric and water companies) and train stations.
   - **Key Methods**:
     - `performAction(Player& player)`: Handles the actions when a player lands on the slot (e.g., paying a fee or using the utility).

## Compiling and Running the Game

To compile and run the game, you can use the provided **Makefile**.

1. **Compile the game**:
   ```bash
   make
