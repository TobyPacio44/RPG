#pragma once
#include <vector>
#include <string>

namespace structures {

    class Map {
    public:
        Map(int width = 10, int height = 10);

        int playerX;
        int playerY;
        int playerMoveCounter = 0;

        void print(int x) const;
        void placePlayer(int x, int y);
        void movePlayer(char direction);
        void moveEnemies();

        void spawnEnemy(int x, int y);
        void spawnItem(int x, int y);
        bool checkEnemyAtPlayer() const;
        bool checkItemAtPlayer() const;

        void removeEnemyAtPlayer();
        void removeItemAtPlayer();

        void loadFromFile(const char* filename);

        char getTile(int x, int y) const;
        void setTile(int x, int y, char value);

    private:
        int width;
        int height;
        std::vector<std::vector<char>> grid;       
    };

}