#ifndef TILE_H
#define TILE_H

#include <string>
#include "Player.h"

class Tile {
private:
    std::string type;
    std::string effect;
    std::string color;
    int strengthChange;
    int staminaChange;
    int wisdomChange;
    int pridePointChange;

    // Helper functions for specific tile effects
    void handleChallenge(Player& player) const;
    void handleOasis(Player& player) const;
    void handleGraveyard(Player& player) const;
    void handleCounseling(Player& player) const;

public:
    Tile();
    Tile(std::string type, std::string effect, std::string color, int strengthChange, int staminaChange, int wisdomChange, int pridePointChange);

    std::string getType() const;
    std::string getEffect() const;
    std::string getColor() const;

    void applyEffect(Player& player) const;
    void displayInfo() const;
};

#endif