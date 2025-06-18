#include "fight.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace structures {

    int calculateModifiedDamage(int baseDamage) {
        // Losujemy procent z zakresu 80 - 120
        int percent = 80 + (rand() % 41); // 80 do 120
        return baseDamage * percent / 100;
    }

    bool checkHit(float hitChance) {
        int roll = rand() % 100; // 0 - 99
        return roll < hitChance*100;
    }

    bool checkCrit() {
        return (rand() % 100) < 10; // 10% szans
    }

    bool fightRound(Character* player, Enemy* enemy) {
        system("cls");

        std::cout << "=== Walka ===\n";
        std::cout << player->name << " HP: " << player->health << "\n";
        std::cout << enemy->name << " HP: " << enemy->health << "\n\n";

        // Atak gracza
        std::cout << player->name << " atakuje...\n";
        if (checkHit(player->weapon.hitChance)) {
            int damage = calculateModifiedDamage(player->baseDamage + player->weapon.attack);
            if (checkCrit()) {
                std::cout << "Trafienie krytyczne!\n";
                damage *= 2;
            }
            //std::cout << player->name << " trafia za " << damage << " obrazen.\n";
            enemy->takeDamage(damage);
        }
        else {
            std::cout << player->name << " chybia!\n";
        }

        if (enemy->health <= 0) {
            std::cout << enemy->name << " zostal pokonany!\n";
            return true;
        }

        Sleep(2000);

        // Atak przeciwnika
        std::cout << enemy->name << " atakuje...\n";
        int damage = calculateModifiedDamage(enemy->baseDamage);
        //std::cout << enemy->name << " trafia za " << damage << " obrazen.\n";
        player->takeDamage(damage);

        if (player->health <= 0) {
            std::cout << player->name << " zostal pokonany!\n";
            return true;
        }

        Sleep(2000);

        return false;
    }

}
