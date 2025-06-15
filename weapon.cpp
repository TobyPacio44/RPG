#include "weapon.h"
#include <cstdlib>  // rand()

namespace structures {

    Weapon generateWeapon(int level) {
        Weapon current;

        int typeNum = rand() % 3;
        current.type = static_cast<WeaponType>(typeNum);

        int maxStat = level * 5;

        switch (current.type) {
        case WeaponType::Sword:
            current.attack = (rand() % (maxStat - 2)) + 3;
            current.hitChance = 0.65f + static_cast<float>(rand() % 25) / 100; // 0.65 do 0.9
            break;

        case WeaponType::Axe:
            current.attack = (rand() % (maxStat - 3)) + 4;
            current.hitChance = 0.50f + static_cast<float>(rand() % 30) / 100; // 0.50 do 0.80
            break;

        case WeaponType::Dagger:
            current.attack = (rand() % (maxStat - 2)) + 3;
            current.hitChance = 0.75f + static_cast<float>(rand() % 25) / 100; // 0.75 do 1.00
            break;
        }

        return current;
    }

}