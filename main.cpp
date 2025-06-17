#include <iostream>
#include <cstdlib>
#include <ctime>

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

    
    Map map;
    map.placePlayer(5, 5);
	map.spawnEnemy(3, 3);
	map.spawnEnemy(5, 7);
	map.spawnEnemy(8, 4);
	map.spawnItem(1, 1);
	map.spawnItem(6, 3);
    //Enemy enemy = Enemy::generateEnemy("Villain", 1);


    char input;
    while (true) {
        system("cls");
        map.print();

        std::cout << "Ruszaj sie [W][A][S][D], (e)kwipunek, (x)wyjdz: ";
        std::cin >> input;
        if (input == 'x') break;

        if (input == 'e') {
            openInventoryMenu(character);
            continue;
        }

        map.movePlayer(input);

        // Sprawdź, czy na nowej pozycji jest wróg
        if (map.checkEnemyAtPlayer()) {
            Enemy* enemy = new Enemy(Enemy::generateEnemy("Villain", floor));
            std::cout << "Spotkales wroga!\n";
            Sleep(1000);

            while (character->health > 0 && enemy->health > 0) {
                if (fightRound(character, enemy)) break;
            }

            if (character->health <= 0) {
                std::cout << "Przegrales walke!\n";
                break;
            }

            map.removeEnemyAtPlayer();
            std::cout << "Wrog pokonany! Kontynuuj eksploracje...\n";
            Sleep(2500);
        }

        if (map.checkItemAtPlayer()) {
            std::cout << "Znalazles przedmiot!\n";
            Item* item = generateRandomItem(floor);
            if (character->inventory.tryAddItem(item, 0, 0)) {
                std::cout << "Dodano do ekwipunku.\n";
            }
            else {
                std::cout << "Brak miejsca – przedmiot przepadl.\n";
                delete item;
            }
            map.removeItemAtPlayer();
            Sleep(2500);
        }
    }

    return 0;
}
