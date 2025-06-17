#include "armor.h"
#include <cstdlib> // dla rand()

namespace structures {

    Armor generateArmor(int level) {
        Armor current;
        int base = level * 5;

        current.armor = (rand() % (base / 2)) + base / 2; // 50–100% z base
        current.durability = (rand() % 21) + 80; // 80–100%

        return current;
    }

}