#ifndef SLOT_HPP
#define SLOT_HPP

// Forward declaration of the Player class
class Player;

class Slot {
public:
    virtual void performAction(Player& player) = 0;  // Use the forward-declared Player class
    virtual void display() const = 0;
    virtual ~Slot() = default;
};

#endif
