#include <iostream>
#include <cstdlib>
#include <ctime>
#include "character.h"
#include "enemy.h"
#include "fight.h"
#include <windows.h>

using namespace structures;

int main() {
    srand(time(nullptr));

    Character character = Character::generateCharacter("Hero", 3);
    Enemy enemy = Enemy::generateEnemy("Villain", 1);

    std::cout << character.name << " HP: " << character.health << std::endl;
    std::cout << enemy.name << " HP: " << enemy.health << std::endl;


    while (character.health > 0 && enemy.health > 0) {
        bool fightOver = fightRound(character, enemy);
        if (fightOver) break;
    }

    return 0;
}
