#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Board.h"
#include "Tile.h"

using namespace std;

// Character structure to hold attributes from characters.txt
struct Character {
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
};

// Function Prototypes
vector<Character> loadCharacters(const string& filename);
void displayCharacters(const vector<Character>& characters);
Character selectCharacter(vector<Character>& characters, const string& playerName);
pair<string, string> selectPathAndAdvisor(const string& playerName);
string selectAdvisor(const string& playerName);
int spinSpinner();
void displayMainMenu(Player player, const Board& board, const vector<Player>& players);

// Main Function
int main() {
    srand(time(0)); // Seed randomness

    // Load characters
    vector<Character> characters = loadCharacters("characters.txt");
    displayCharacters(characters);

    // Ask for the number of players
    int numPlayers;
    while (true) {
        cout << "Enter the number of players (2 or 3): ";
        cin >> numPlayers;
        if (numPlayers == 2 || numPlayers == 3) {
            break;
        }
        cout << "Invalid input. Please enter 2 or 3.\n";
    }

    // Player setup
    vector<Player> players;
    for (int i = 1; i <= numPlayers; ++i) {
        cout << "Player " << i << ", enter your name: ";
        string playerName;
        cin >> playerName;

        Character selectedCharacter = selectCharacter(characters, playerName);
        auto pathAndAdvisor = selectPathAndAdvisor(playerName);

        Player player(selectedCharacter.name, selectedCharacter.age,
                      selectedCharacter.strength, selectedCharacter.stamina,
                      selectedCharacter.wisdom, selectedCharacter.pridePoints);
        player.setPath(pathAndAdvisor.first);
        player.setAdvisor(pathAndAdvisor.second);

        players.push_back(player);
    }

    // Initialize board
    Board board;
    board.setPlayerCount(numPlayers);
    board.initializeBoard(players[0].getPath(), players[1].getPath());

    // Display initial board state
    cout << "\nInitial Board State:\n";
    board.displayBoard(players);

    // Gameplay loop
    bool gameRunning = true;
    int currentPlayerIndex = 0;

    while (gameRunning) {
        Player& current = players[currentPlayerIndex];

        cout << "\n" << current.getName() << "'s Turn! Press Enter to continue or type 1 to access Main Menu: ";
        cin.ignore();
        string input;
        getline(cin, input);

        if (input == "1") {
            displayMainMenu(current, board, players);
            continue; // Return to the same player's turn
        }

        // Spin spinner and move forward
        cout << "\n" << current.getName() << "'s Turn! Spinning the spinner...\n";
        int steps = spinSpinner();
        cout << current.getName() << " moves forward " << steps << " steps.\n";

        // Move player
        board.movePlayer(currentPlayerIndex + 1, steps);
        current.setPosition(min(current.getPosition() + steps, 51)); // Cap at board limit

        // Tile interaction
        Tile tile = board.getTileAt(currentPlayerIndex % 2, current.getPosition());
        tile.displayInfo();
        tile.applyEffect(current);

        // Display updated board
        cout << "\nUpdated Board State:\n";
        board.displayBoard(players);

        // Check for game end
        if (current.getPosition() >= 51) {
            cout << "\n" << current.getName() << " has reached Pride Rock!\n";
        }

        // Final Evaluation when all players reach the final tile
        if (all_of(players.begin(), players.end(), [](const Player& p) { return p.getPosition() >= 51; })) {
            for (Player& player : players) {
                int bonusPridePoints = (player.getStrength() / 100 + player.getStamina() / 100 + player.getWisdom() / 100) * 1000;
                player.setPridePoints(player.getPridePoints() + bonusPridePoints);
            }

            // Display final stats
            cout << "\nFinal Stats:\n";
            for (const Player& player : players) {
                player.displayStats();
            }

            // Determine the winner
            auto winner = max_element(players.begin(), players.end(),
                                      [](const Player& a, const Player& b) { return a.getPridePoints() < b.getPridePoints(); });
            cout << "\nThe winner is " << winner->getName() << " with " << winner->getPridePoints() << " Pride Points!\n";

            gameRunning = false;
        }

        // Switch turn
        currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
    }

    cout << "\nGame Over! Thanks for playing!\n";
    return 0;
}

// Function Definitions
vector<Character> loadCharacters(const string& filename) {
    vector<Character> characters;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#' || line == "playerName|age|strength|stamina|wisdom|pridePoints") {
            continue;
        }

        stringstream ss(line);
        Character character;

        getline(ss, character.name, '|');
        ss >> character.age;
        ss.ignore(1, '|');
        ss >> character.strength;
        ss.ignore(1, '|');
        ss >> character.stamina;
        ss.ignore(1, '|');
        ss >> character.wisdom;
        ss.ignore(1, '|');
        ss >> character.pridePoints;

        characters.push_back(character);
    }

    file.close();
    return characters;
}

void displayCharacters(const vector<Character>& characters) {
    cout << "Available Characters:\n";
    for (const auto& character : characters) {
        cout << "Name: " << character.name
             << ", Age: " << character.age
             << ", Strength: " << character.strength
             << ", Stamina: " << character.stamina
             << ", Wisdom: " << character.wisdom
             << ", Pride Points: " << character.pridePoints
             << endl;
    }
}

Character selectCharacter(vector<Character>& characters, const string& playerName) {
    while (true) {
        cout << playerName << ", select your character by name: ";
        string selectedName;
        cin >> selectedName;

        auto it = find_if(characters.begin(), characters.end(), [&selectedName](const Character& c) {
            return c.name == selectedName;
        });

        if (it != characters.end()) {
            Character selectedCharacter = *it;
            characters.erase(it);
            return selectedCharacter;
        } else {
            cout << "Invalid selection. Please choose a valid character.\n";
        }
    }
}

pair<string, string> selectPathAndAdvisor(const string& playerName) {
    string path;
    string advisor = "None";

    while (true) {
        cout << playerName << ", choose your path: (1) Cub Training or (2) Straight to the Pride Lands: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            path = "Cub Training";
            advisor = selectAdvisor(playerName);
            break;
        } else if (choice == 2) {
            path = "Straight to the Pride Lands";
            break;
        } else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }

    return {path, advisor};
}

string selectAdvisor(const string& playerName) {
    cout << playerName << ", select your advisor:\n"
         << "1. Rafiki - Invisibility\n"
         << "2. Nala - Night Vision\n"
         << "3. Sarabi - Energy Manipulation\n"
         << "4. Zazu - Weather Control\n"
         << "5. Sarafina - Super Speed\n";

    while (true) {
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: return "Rafiki";
            case 2: return "Nala";
            case 3: return "Sarabi";
            case 4: return "Zazu";
            case 5: return "Sarafina";
            default: cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
}

int spinSpinner() {
    return (rand() % 6) + 1;
}

void displayMainMenu(Player player, const Board& board, const vector<Player>& players) {
    while (true) {
        cout << "\nMain Menu: Select an option to continue\n";
        cout << "1. Check Player Progress\n";
        cout << "2. Review Character\n";
        cout << "3. Check Position\n";
        cout << "4. Review Your Advisor\n";
        cout << "5. Back to Turn\n";
        cout << "Please choose an option using the corresponding number: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                player.displayStats();
                break;
            }
            case 2: {
                cout << "Name: " << player.getName() << ", Age: " << player.getAge() << endl;
                break;
            }
            case 3: {
                board.displayBoard(players);
                break;
            }
            case 4: {
                cout << "Your Advisor: " << player.getAdvisor() << endl;
                break;
            }
            case 5: {
                return;
            }
            default: {
                cout << "Invalid choice. Please select again.\n";
            }
        }
    }
}