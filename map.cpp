#include "map.h"
#include <iostream>
#include <windows.h>

structures::Map::Map(int w, int h) : width(w), height(h), playerX(0), playerY(0) {
    // Inicjalizacja planszy
    grid.resize(height, std::vector<char>(width, '.'));
}

void structures::Map::print(int floor) const {
    if (floor < 5) {
        std::cout << "===== Floor " << floor << " =====\n";
	}
	else {
		std::cout << "=== Final Floor ===\n";
	}
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == playerX && y == playerY)
                std::cout << 'P' << ' ';
            else
                std::cout << grid[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

void structures::Map::placePlayer(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        playerX = x;
        playerY = y;
    }
}

void structures::Map::movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;

    switch (direction) {
    case 'W': case 'w': newY--; break;
    case 'S': case 's': newY++; break;
    case 'A': case 'a': newX--; break;
    case 'D': case 'd': newX++; break;
    default:
        std::cout << "Nieprawidlowy ruch!\n";
        return;
    }

    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
        if (grid[newY][newX] != '#') {
            placePlayer(newX, newY);
        }
        else {
            std::cout << "Nie mozesz wejsc na przeszkode!\n";
            Sleep(500); // by gracz zobaczy³ komunikat
        }
    }
    else {
        std::cout << "Nie mozesz wyjsc poza mape!\n";
        Sleep(500);
    }

}
void structures::Map::spawnEnemy(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        if (grid[y][x] == '.') {
            grid[y][x] = 'E';
        }
        else {
            std::cout << "Pole zajete, nie mozna zespawnowac wroga.\n";
        }
    }
}

void structures::Map::spawnItem(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height && grid[y][x] == '.') {
        grid[y][x] = 'I';
    }
}

bool structures::Map::checkEnemyAtPlayer() const {
    return grid[playerY][playerX] == 'E';
}

bool structures::Map::checkItemAtPlayer() const {
    return grid[playerY][playerX] == 'I';
}

void structures::Map::removeEnemyAtPlayer() {
    if (grid[playerY][playerX] == 'E') {
        grid[playerY][playerX] = '.';
    }
}

void structures::Map::removeItemAtPlayer() {
    if (grid[playerY][playerX] == 'I') {
        grid[playerY][playerX] = '.';
    }
}

void structures::Map::loadFromFile(const char* filename) {
    FILE* file;
	errno_t err = fopen_s(&file, filename, "r");
    if (!file) {
        std::cout << "Blad: Nie mozna otworzyc " << filename << "\n";
        return;
    }

    char line[128];
    int y = 0;
    while (fgets(line, sizeof(line), file) && y < height) {
        for (int x = 0; x < width && line[x] != '\n' && line[x] != '\0'; ++x) {
            switch (line[x]) {
            case 'P': placePlayer(x, y); break;
            case 'E': spawnEnemy(x, y); break;
            case 'I': spawnItem(x, y); break;
            case '#': grid[y][x] = '#'; break;
            case 'X': grid[y][x] = 'X'; break;
            default: grid[y][x] = '.'; break;
            }
        }
        ++y;
    }

    fclose(file);
}


