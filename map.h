#pragma once
#include <vector>
#include <string>

namespace structures {

    class Map {
    public:
        Map(int width = 10, int height = 10);

        void print() const;
        void placePlayer(int x, int y);
        void movePlayer(char direction);

        void spawnEnemy(int x, int y);
        void spawnItem(int x, int y);
        bool checkEnemyAtPlayer() const;
        bool checkItemAtPlayer() const;
        void removeEnemyAtPlayer();
        void removeItemAtPlayer();

    private:
        int width;
        int height;
        std::vector<std::vector<char>> grid;

        int playerX;
        int playerY;
    };

}