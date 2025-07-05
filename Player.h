#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

using namespace std;

class Player {
private:
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
    int position;
    string path;    // Stores the player's chosen path
    string advisor; // Stores the player's chosen advisor (if any)

public:
    // Constructor
    Player(string name, int age, int strength, int stamina, int wisdom, int pridePoints);

    // Getters
    string getName() const;
    int getAge() const;
    int getStrength() const;
    int getStamina() const;
    int getWisdom() const;
    int getPridePoints() const;
    int getPosition() const;
    string getPath() const;       // Getter for path
    string getAdvisor() const;    // Getter for advisor

    // Setters
    void setPosition(int newPosition);
    void setStrength(int newStrength);
    void setStamina(int newStamina);
    void setWisdom(int newWisdom);
    void setPridePoints(int newPridePoints);
    void setPath(const string& newPath);       // Setter for path
    void setAdvisor(const string& newAdvisor); // Setter for advisor

    // Update stats
    void updateStats(int strengthChange, int staminaChange, int wisdomChange, int pridePointChange);

    // Display player stats
    void displayStats() const;
};

#endif