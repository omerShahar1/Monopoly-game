#ifndef BOARD_HPP
#define BOARD_HPP

#include "Slot.hpp"
#include <vector>
#include <memory>

class Board {
public:
    Board();
    void display() const;
    Slot* getSlot(int position) const;  // This declaration must exist
    void drawBoard(const std::vector<Player>& players) const;

private:
    std::vector<std::unique_ptr<Slot>> slots;
    void initializeSlots();
    void printSlot(int index, const std::vector<Player>& players, bool vertical = false) const;
};

#endif
