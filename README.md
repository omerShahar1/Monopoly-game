# Monopoly Game - C++ Implementation

This is a simple console-based implementation of the Monopoly board game, written in C++. The game allows 2-8 players to play on the same computer, each controlling a piece on the Monopoly board. Players can buy properties, build houses and hotels, and pay rent. The game continues until one player is left or someone wins with a balance of at least 4000 units.

## Table of Contents
- [Game Rules](#game-rules)
- [How to Play](#how-to-play)
- [Classes and Objects](#classes-and-objects)
- [Compiling and Running the Game](#compiling-and-running-the-game)

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








# Monopoly Game - C++ Implementation

This project is a simple console-based implementation of the Monopoly board game. The game is designed for 2-8 players playing on the same computer. Players can buy properties, build houses and hotels, pay rent, and go bankrupt. The game continues until only one player remains or a player wins with a balance of at least 4000 units.

## Table of Contents
- [Game Rules](#game-rules)
- [How to Play](#how-to-play)
- [Classes and Functions](#classes-and-functions)
  - [Game Class](#game-class)
  - [Player Class](#player-class)
  - [Board Class](#board-class)
  - [Slot Class (Abstract)](#slot-class-abstract)
  - [Street Class](#street-class)
  - [Special Slot Classes](#special-slot-classes)
  - [Utility and TrainStation Classes](#utility-and-trainstation-classes)
- [Compiling and Running the Game](#compiling-and-running-the-game)
- [Testing the Game](#testing-the-game)
- [Future Improvements](#future-improvements)

---

## Game Rules

1. The game consists of a board with 40 slots. Each slot represents a street, train station, utility, or special action slot.
2. Players roll two dice and move around the board based on the dice result.
3. When a player lands on a street, they can purchase it if it is unowned. If another player owns the street, rent must be paid.
4. Players can build houses and hotels on their streets once they own all streets in a particular color group.
   - The rent increases with each house, and the rent for a hotel is the highest.
5. Special slots include:
   - **Go**: Players collect $200 when they pass or land on "Go."
   - **Jail**: Players can go to jail by landing on the "Go to Jail" slot or by rolling doubles three times in a row.
   - **Surprise Slots**: Provide random events such as bonuses, fines, or special cards.
6. Players can go bankrupt if they cannot afford to pay rent or taxes. Bankrupt players are removed from the game.
7. The game ends when only one player remains or a player has a balance of 4000 units.

---

## How to Play

1. At the start of the game, enter the number of players (2 to 8) and assign names.
2. Each player will take turns rolling two dice and moving around the board.
3. If a player lands on an unowned property, they can buy it. If they land on an owned property, they must pay rent.
4. Players can build houses and hotels on properties they own, increasing the rent other players must pay.
5. The game ends when one player is left or a player has a balance of 4000 units.

---

## Classes and Functions

### **Game Class**

- **Purpose**: The `Game` class is responsible for managing the flow of the game, including player turns, dice rolls, and game over conditions.

#### Functions:
1. **`Game(int numPlayers, const std::vector<std::string>& playerSymbols)`**: Constructor that initializes the game with a given number of players and their symbols.
   
2. **`void start()`**: Starts the game, runs the main game loop, and processes each player's turn.

3. **`void takeTurn(Player& player)`**: Handles a player's turn. Rolls the dice, moves the player, and calls the relevant actions based on the slot the player lands on.

4. **`bool isGameOver() const`**: Checks if the game has ended. The game ends if only one player remains.

5. **`void displayStatus() const`**: Displays the current status of all players, showing their balance.

6. **`std::vector<Player>& getPlayers()`**: Returns a reference to the list of players in the game.

7. **`void setupPlayers(int numPlayers, const std::vector<std::string>& playerSymbols)`**: Initializes the players with names and symbols based on user input.

---

### **Player Class**

- **Purpose**: The `Player` class represents a player in the game. It manages the player's name, position on the board, balance, and properties.

#### Functions:
1. **`Player(const std::string& name, const std::string& symbol)`**: Constructor that initializes a player with a name and symbol.
   
2. **`std::string getName() const`**: Returns the player's name.

3. **`std::string getSymbol() const`**: Returns the player's symbol (e.g., "♟", "♞").

4. **`int getPosition() const`**: Returns the player's current position on the board.

5. **`void setPosition(int newPosition)`**: Sets the player's position on the board.

6. **`void move(int diceRoll)`**: Moves the player forward by the number of spaces indicated by the dice roll. Wraps around the board if necessary.

7. **`int getMoney() const`**: Returns the player's current balance.

8. **`void pay(int amount, Player* creditor = nullptr)`**: Deducts money from the player's balance. If a creditor is provided, the creditor receives the payment.

9. **`bool isBankrupt() const`**: Checks whether the player is bankrupt (i.e., has a balance of $0 or less).

10. **`void addProperty(Slot* property)`**: Adds a property to the player's list of owned properties.

---

### **Board Class**

- **Purpose**: The `Board` class represents the Monopoly board. It manages the 40 slots and handles actions that take place on the board.

#### Functions:
1. **`Board()`**: Constructor that initializes the board with 40 slots (streets, utilities, train stations, and special slots).

2. **`Slot* getSlot(int position) const`**: Returns the slot at the given position on the board.

3. **`void drawBoard(const std::vector<Player>& players) const`**: Draws a visual representation of the board in the console, showing player positions and slot ownership.

4. **`void initializeSlots()`**: Initializes the different types of slots (streets, utilities, train stations, etc.) on the board.

---

### **Slot Class (Abstract)**

- **Purpose**: The `Slot` class is an abstract base class representing a generic slot on the Monopoly board. All specific slots (e.g., streets, utilities, special slots) inherit from this class.

#### Functions:
1. **`virtual void performAction(Player& player) = 0`**: Pure virtual function that defines the action that occurs when a player lands on the slot. Must be implemented by derived classes.

---

### **Street Class**

- **Purpose**: The `Street` class represents a street property on the board. Players can buy streets, build houses and hotels, and charge rent to other players.

#### Functions:
1. **`Street(const std::string& name, const std::string& color, int price, int rent, int housePrice, int hotelPrice)`**: Constructor that initializes a street with its name, color, price, rent, house price, and hotel price.
   
2. **`void performAction(Player& player)`**: Handles the action that occurs when a player lands on the street. If the street is unowned, the player can buy it. If the street is owned by another player, rent must be paid.

3. **`void buildHouse()`**: Allows the player to build a house on the street, provided they own it. If the player builds four houses, they can then build a hotel.

4. **`int getHouses() const`**: Returns the current number of houses on the street.

5. **`std::string getColor() const`**: Returns the color group of the street.

6. **`std::string getName() const`**: Returns the name of the street.

7. **`Player* getOwner() const`**: Returns the player who owns the street (or `nullptr` if unowned).

8. **`void display() const`**: Displays the details of the street, including its name, color, and price.

---

### **Special Slot Classes**

- **Purpose**: These classes represent special slots on the board, such as tax slots, free parking, surprise slots, and jail.

#### Functions:
1. **TaxSlot**: Deducts a fixed amount from the player's balance when they land on it.
   
2. **FreeParkingSlot**: No action occurs when a player lands here.
   
3. **GoToJailSlot**: Sends the player to jail when they land on this slot.

4. **SurpriseSlot**: Implements random events, such as awarding money or giving a "Get Out of Jail Free" card.

---

### **Utility and TrainStation Classes**

- **Purpose**: These classes represent the utility (Electric and Water companies) and train station slots. Players can purchase them, and others must pay fees when landing on them.

#### Functions:
1. **`void performAction(Player& player)`**: Handles the action when a player lands on the utility or train station. The fee or rent is determined by the number of utilities/stations owned by the player.

---

## Compiling and Running the Game

To compile and run the game, you can

