#pragma once
#include <string>

namespace structures {

    struct Entity {
        std::string name;
        int health = 100;
        int baseArmor = 1;
        int baseDamage = 1;
        int mana = 0;
        int posx = 0;
        int posy = 0;

        virtual void takeDamage(int damage) {
            if (damage > 0) {
                health -= damage;
            }
            else {
                health -= 1;
            }
        }

        virtual bool isAlive() const {
            return health > 0;
        }
    };

}