#include "Board.h"
#include <cstdlib> // For randomization
#include <ctime>   // For seeding randomness
#include <iostream>

#define RESET "\033[0m"

// Constructor
Board::Board() {
    _player_count = 0;

    // Initialize all tiles using the default constructor
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < _BOARD_SIZE; ++j) {
            _tiles[i][j] = Tile(); // Default tiles
        }
    }
}

// Set the number of players
void Board::setPlayerCount(int player_count) {
    _player_count = player_count;
}

// Initialize the board with different paths
void Board::initializeBoard(const std::string& path1, const std::string& path2) {
    srand(time(0)); // Seed randomness

    // Initialize tiles for Player 1's path
    initializeTiles(0, path1);

    // Initialize tiles for Player 2's path
    initializeTiles(1, path2);
}

// Initialize tiles for a specific path
void Board::initializeTiles(int pathIndex, const std::string& pathType) {
    for (int i = 0; i < _BOARD_SIZE; ++i) {
        std::string type, effect, color;

        if (i == 0) {
            // Start tile
            type = "Start";
            color = "Grey";
            effect = "Starting Tile";
        } else if (i == _BOARD_SIZE - 1) {
            // End tile
            type = "Pride Rock";
            color = "Orange";
            effect = "End of the game!";
        } else {
            int tileType = rand() % 5;

            switch (tileType) {
                case 0: type = "Regular"; color = "Green"; effect = "Random Event"; break;
                case 1: type = "Oasis"; color = "Blue"; effect = "Gain resources and extra turn"; break;
                case 2: type = "Graveyard"; color = "Red"; effect = "Move back 10 tiles"; break;
                case 3: type = "Counseling"; color = "Pink"; effect = "Choose or change an advisor"; break;
                case 4: type = "Challenge"; color = "Purple"; effect = "Answer a riddle for Wisdom"; break;
            }
        }

        _tiles[pathIndex][i] = Tile(type, effect, color, 0, 0, 0, 0);
    }
}

// Display the entire board with player positions
void Board::displayBoard(const std::vector<Player>& players) const {
    std::cout << "Board State:\n";

    for (int pathIndex = 0; pathIndex < 2; ++pathIndex) {
        for (int i = 0; i < _BOARD_SIZE; ++i) {
            const Tile& tile = _tiles[pathIndex][i];
            std::string tileColor = tile.getColor();

            // Check if any player is on the current tile
            bool playerOnTile = false;
            for (size_t playerIndex = 0; playerIndex < players.size(); ++playerIndex) {
                if (players[playerIndex].getPosition() == i && players[playerIndex].getPath() == (pathIndex == 0 ? "Cub Training" : "Straight to the Pride Lands")) {
                    std::cout << tileColor << "P" << (playerIndex + 1) << RESET << " ";
                    playerOnTile = true;
                    break;
                }
            }

            if (!playerOnTile) {
                std::cout << tileColor << "  " << RESET << " ";
            }
        }
        std::cout << "\n";
    }
}

// Move a player forward by a certain number of steps
void Board::movePlayer(int playerId, int steps) {
    // Player positions are managed by Player objects, so no updates here.
}

// Get the tile at a specific position on a path
Tile Board::getTileAt(int pathIndex, int pos) const {
    return _tiles[pathIndex][pos];
}