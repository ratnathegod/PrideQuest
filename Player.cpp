#include "Player.h"
#include <algorithm> // For std::max

using namespace std;

// Constructor
Player::Player(string name, int age, int strength, int stamina, int wisdom, int pridePoints)
    : name(name), age(age), strength(strength), stamina(stamina),
      wisdom(wisdom), pridePoints(pridePoints), position(0), path(""), advisor("None") {}

// Getters
string Player::getName() const { return name; }
int Player::getAge() const { return age; }
int Player::getStrength() const { return strength; }
int Player::getStamina() const { return stamina; }
int Player::getWisdom() const { return wisdom; }
int Player::getPridePoints() const { return pridePoints; }
int Player::getPosition() const { return position; }
string Player::getPath() const { return path; }
string Player::getAdvisor() const { return advisor; } // Getter for advisor

// Setters
void Player::setPosition(int newPosition) { position = max(0, newPosition); }
void Player::setStrength(int newStrength) { strength = max(0, newStrength); }
void Player::setStamina(int newStamina) { stamina = max(0, newStamina); }
void Player::setWisdom(int newWisdom) { wisdom = max(0, newWisdom); }
void Player::setPridePoints(int newPridePoints) { pridePoints = max(0, newPridePoints); }
void Player::setPath(const string& newPath) { path = newPath; }
void Player::setAdvisor(const string& newAdvisor) { advisor = newAdvisor; } // Setter for advisor

// Update multiple stats at once
void Player::updateStats(int strengthChange, int staminaChange, int wisdomChange, int pridePointChange) {
    strength = max(0, strength + strengthChange);
    stamina = max(0, stamina + staminaChange);
    wisdom = max(0, wisdom + wisdomChange);
    pridePoints = max(0, pridePoints + pridePointChange);
}

// Display player stats
void Player::displayStats() const {
    cout << "Name: " << name << "\n"
         << "Age: " << age << "\n"
         << "Strength: " << strength << "\n"
         << "Stamina: " << stamina << "\n"
         << "Wisdom: " << wisdom << "\n"
         << "Pride Points: " << pridePoints << "\n"
         << "Position: " << position << "\n"
         << "Path: " << path << "\n"
         << "Advisor: " << advisor << "\n";
}