#include <iostream>
#include <cstdlib>
#include <ctime>

#include <conio.h>
#include <windows.h>
#include "character.h"
#include "enemy.h"
#include "fight.h"
#include "map.h"
#include "item.h"
#include "item_generator.h"
#include "inventory_menu.h"

using namespace structures;

int main() {
    srand(time(nullptr));

    int floor = 1;

    Character* character = new Character(Character::generateCharacter("Hero", floor));
    character->inventory.tryAddItem(generatePotion(floor), 0, 0);

    bool (*fightFn)(Character*, Enemy*, void (*)(Enemy*, Character*)) = &structures::fightRound;
    void (*attackFn)(Enemy*, Character*) = &structures::regularEnemyAttack;
    
    Map map;
    char filename[32];
    sprintf_s(filename, sizeof(filename), "level%d.txt", floor);
    map.loadFromFile(filename);

    system("cls");
    map.print(floor);
    std::cout << "Move [W][A][S][D], (i)nventory, e(x)it: ";

    char input;
    while (true) {
        if (!_kbhit())
            continue;

        input = _getch();

        map.movePlayer(input);

        system("cls");
        map.print(floor);

        std::cout << "Move [W][A][S][D], (i)nventory, e(x)it:";

        if (input == 'x') break;

        if (input == 'i') {
            openInventoryMenu(character);
            system("cls");
            map.print(floor);
            std::cout << "Move [W][A][S][D], (i)nventory, e(x)it: ";
            continue;
        }


        // Przejście na kolejny poziom
        if (map.playerX == 8 && map.playerY == 8) {
            if (floor < 5) {
                floor++;
                std::cout << "\nLoading next level: " << floor << "...\n";
                Sleep(1500);

                map = Map(); // nowa mapa
                sprintf_s(filename, sizeof(filename), "level%d.txt", floor);
                map.loadFromFile(filename);

                map.placePlayer(1, 1); // Start w rogu
            }
            else {
                std::cout << "You have beaten all levels!\n";
                break;
            }
        }

        // Sprawdź, czy na nowej pozycji jest wróg
        if (map.checkEnemyAtPlayer()) {
			Enemy* enemy = new Enemy(Enemy::generateEnemy("Villain", floor));

            if (floor == 5) {
                delete enemy;
                enemy = new Enemy(Enemy::generateEnemy("Final Boss", 10));
                //Tutaj podmieniamy funkcję ataku na bossową
                attackFn = &structures::bossEnemyAttack;
				std::cout << "\nYou have encountered the Final Boss!";
            }
            else {
                std::cout << "\nEnemy encounter!\n";
            }
            Sleep(1000);

            while (character->health > 0 && enemy->health > 0) {
                if (fightFn(character, enemy, attackFn)) break;
            }

            if (character->health <= 0) {
                std::cout << "You lost!\n";
                break;
            }

            map.removeEnemyAtPlayer();
            delete enemy;
            std::cout << "Enemy defeated! Continue your journey...\n";
            Sleep(2500);
        }

        if (map.checkItemAtPlayer()) {
            Item* item = generateRandomItem(floor+1);
            std::cout << "\nYou found: "<< item->name <<"\n";
            if (character->inventory.tryAddItem(item, 0, 0)) {
                std::cout << "Added to inventory.\n";
            }
            else {
                std::cout << "No space - item deleted.\n";
                delete item;
            }
            map.removeItemAtPlayer();
            Sleep(2500);
        }
    }

    delete character;
    return 0;
}
