#include "fight.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace structures {

    int calculateModifiedDamage(int baseDamage) {
        // Losowe zmodyfikowanie obra¿eñ: 80–120% bazowych
        int percent = 80 + (rand() % 41);
        return baseDamage * percent / 100;
    }

    bool checkHit(float hitChance) {
        int roll = rand() % 100; // 0 - 99
        return roll < hitChance*100;
    }

    bool checkCrit() {
        // Szansa trafienia (0.0–1.0)
        return (rand() % 100) < 10;
    }

    bool fightRound(Character* player, Enemy* enemy, void (*enemyAttackFn)(Enemy*, Character*)) {
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

        Sleep(1000);

        //Atak przeciwnika
        std::cout <<"\n";
        std::cout << enemy->name << " atakuje...\n";
        enemyAttackFn(enemy, player);

        if (player->health <= 0) {
            std::cout << player->name << " zostal pokonany!\n";
            return true;
        }

        Sleep(4000);

        return false;
    }

    void regularEnemyAttack(Enemy* enemy, Character* player) {
        int damage = calculateModifiedDamage(enemy->baseDamage);
        player->takeDamage(damage);
    }

    void bossEnemyAttack(Enemy* enemy, Character* player) {
        int damage = calculateModifiedDamage(enemy->baseDamage + 5); // silniejszy
        std::cout << "\n[Boss] zadaje potezny cios!\n";
        player->takeDamage(damage);

        // Bonusowy atak (np. 20% szans)
        if ((rand() % 100) < 20) {
            std::cout << "\n[Boss] wykonuje dodatkowy atak!\n";
            int extra = calculateModifiedDamage(enemy->baseDamage / 2);
            player->takeDamage(extra);
        }
    }
}
