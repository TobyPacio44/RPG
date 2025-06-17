#include "weapon.h"
#include <cstdlib>  // rand()

namespace structures {

    Weapon generateWeapon(int level) {
        Weapon current;

        int typeNum = rand() % 3;
        current.type = static_cast<WeaponType>(typeNum);

        int maxStat = level * 10;

        switch (current.type) {
        case WeaponType::Sword:
            current.attack = ((rand() % 4) + 8) * maxStat / 10; // 8–11 * maxStat
            current.hitChance = 0.65f + (rand() % 25) / 100; // 0.65 do 0.9
            break;

        case WeaponType::Axe:
            current.attack = ((rand() % 5) + 11) * maxStat / 10; // 11–15 * maxStat
            current.hitChance = 0.50f + (rand() % 30) / 100; // 0.50 do 0.80
            break;

        case WeaponType::Dagger:
            current.attack = ((rand() % 4) + 4) * maxStat / 10; // 4–7 * maxStat
            current.hitChance = 0.75f + (rand() % 25) / 100; // 0.75 do 1.00
            break;
        }

        return current;
    }


}