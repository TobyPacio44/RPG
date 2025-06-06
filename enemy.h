#pragma once
#include "entity.h"

namespace structures {

    struct Enemy : public Entity {
        std::string name;

        static Enemy generateEnemy(const std::string& Name, int level) {
            Enemy enemy;
            enemy.name = Name;
            enemy.health = 50 + rand() % (level * 10);
            enemy.baseArmor = rand() % (level * 3) + 2;
            enemy.baseDamage = rand() % (level * 4) + 2;
            enemy.mana = 10;
            return enemy;
        }

        void attackEntity(Entity& target) {
            int damage = baseDamage;
            target.takeDamage(damage);
            std::cout << "Enemy hits for " << damage << " damage!\n";
        }
    };

}