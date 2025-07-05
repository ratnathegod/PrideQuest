#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Player.h"
#include <vector>
#include <string>

class Board {
private:
    static const int _BOARD_SIZE = 52; // Board size
    Tile _tiles[2][_BOARD_SIZE];       // 2D array for two paths
    int _player_count;                // Number of players

    // Helper function to initialize tiles for a specific path
    void initializeTiles(int pathIndex, const std::string& pathType);

public:
    Board();
    void setPlayerCount(int player_count);
    void initializeBoard(const std::string& path1, const std::string& path2);

    // Display board with player positions
    void displayBoard(const std::vector<Player>& players) const;

    void movePlayer(int playerId, int steps);
    Tile getTileAt(int pathIndex, int pos) const;
};

#endif