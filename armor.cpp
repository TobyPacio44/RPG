#include "armor.h"
#include <cstdlib> // dla rand()

namespace structures {

    Armor generateArmor(int level) {
        Armor current;
        int num;

        num = rand() % (level * 5) + 1;
        current.armor = num;

        num = rand() % (level * 5) + 1;
        current.durability = num;

        num = rand() % (level * 5) + 1;
        current.fireDurability = num;

        num = rand() % (level * 5) + 1;
        current.iceDurability = num;

        return current;
    }

}