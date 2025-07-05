#include "Tile.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Default constructor
Tile::Tile() : type("Regular"), effect("Random Event"), color("White"),
               strengthChange(0), staminaChange(0), wisdomChange(0), pridePointChange(0) {}

// Parameterized constructor
Tile::Tile(std::string type, std::string effect, std::string color, int strengthChange, int staminaChange, int wisdomChange, int pridePointChange)
    : type(type), effect(effect), color(color),
      strengthChange(strengthChange), staminaChange(staminaChange),
      wisdomChange(wisdomChange), pridePointChange(pridePointChange) {}

// Getter methods
std::string Tile::getType() const {
    return type;
}

std::string Tile::getEffect() const {
    return effect;
}

std::string Tile::getColor() const {
    if (color == "Red") return "\033[48;2;230;10;10m";    // Red
    if (color == "Green") return "\033[48;2;34;139;34m";  // Green
    if (color == "Blue") return "\033[48;2;10;10;230m";   // Blue
    if (color == "Pink") return "\033[48;2;255;105;180m"; // Pink
    if (color == "Purple") return "\033[48;2;128;0;128m"; // Purple
    if (color == "Orange") return "\033[48;2;230;115;0m"; // Orange
    if (color == "Grey") return "\033[48;2;128;128;128m"; // Grey
    return "\033[0m"; // Reset
}

// Display tile information
void Tile::displayInfo() const {
    cout << "Tile Type: " << type << "\nEffect: " << effect << "\nColor: " << color << endl;
}

// Apply effect to the player
void Tile::applyEffect(Player& player) const {
    if (type == "Challenge") {
        handleChallenge(player);
    } else if (type == "Oasis") {
        handleOasis(player);
    } else if (type == "Graveyard") {
        handleGraveyard(player);
    } else if (type == "Counseling") {
        handleCounseling(player);
    }
}

// Handle Challenge tile
void Tile::handleChallenge(Player& player) const {
    cout << "You face a challenge! Solve a riddle to gain Wisdom.\n";
    ifstream file("riddles.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open riddles.txt\n";
        return;
    }

    vector<pair<string, string>> riddles;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '/') continue;

        stringstream ss(line);
        string question, answer;

        if (getline(ss, question, '|') && getline(ss, answer, '|')) {
            riddles.push_back({question, answer});
        }
    }
    file.close();

    if (riddles.empty()) {
        cout << "No riddles available.\n";
        return;
    }

    srand(time(0));
    int index = rand() % riddles.size();
    cout << "Riddle: " << riddles[index].first << "\nYour Answer: ";
    string userAnswer;
    cin.ignore();
    getline(cin, userAnswer);

    if (userAnswer == riddles[index].second) {
        cout << "Correct! You gain 50 wisdom.\n";
        player.setWisdom(player.getWisdom() + 50);
    } else {
        cout << "Wrong! The correct answer was: " << riddles[index].second << "\n";
    }
}

// Handle Oasis tile
void Tile::handleOasis(Player& player) const {
    cout << "You found an oasis! Gaining 100 stamina and pride points.\n";
    player.setStamina(player.getStamina() + 100);
    player.setPridePoints(player.getPridePoints() + 100);
}

// Handle Graveyard tile
void Tile::handleGraveyard(Player& player) const {
    cout << "You stumbled upon a graveyard! Losing 50 strength and moving back 2 tiles.\n";
    player.setStrength(player.getStrength() - 50);
    player.setPosition(max(0, player.getPosition() - 2));
}

// Handle Counseling tile
void Tile::handleCounseling(Player& player) const {
    cout << "Counseling: Change or choose an advisor!\n";
    cout << player.getName() << ", select your advisor:\n"
         << "1. Rafiki - Invisibility\n"
         << "2. Nala - Night Vision\n"
         << "3. Sarabi - Energy Manipulation\n"
         << "4. Zazu - Weather Control\n"
         << "5. Sarafina - Super Speed\n";

    string newAdvisor;
    while (true) {
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: newAdvisor = "Rafiki"; break;
            case 2: newAdvisor = "Nala"; break;
            case 3: newAdvisor = "Sarabi"; break;
            case 4: newAdvisor = "Zazu"; break;
            case 5: newAdvisor = "Sarafina"; break;
            default:
                cout << "Invalid choice. Please select a number between 1 and 5.\n";
                continue;
        }
        break;
    }

    player.setAdvisor(newAdvisor);
    cout << "Your new advisor is: " << newAdvisor << endl;
}