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
            enemy.baseDamage = rand() % (level * 5) + 2;
            enemy.mana = 10;
            return enemy;
        }

        void takeDamage(int damage) override {
            float reductionFactor = getArmorReduction(baseArmor);
            int reduced = (int)(damage * reductionFactor);
            if (reduced <= 0) reduced = 1;

            std::cout << "Enemy takes " << reduced << " damage\n";
            Entity::takeDamage(reduced);
        }

        float getArmorReduction(int armorValue) {
            if (armorValue <= 0) return 1.0f;
            if (armorValue >= 100) return 0.30f;

            float logBase = log(101.0f);
            float reduction = 1.0f - (log((float)(armorValue + 1)) / logBase);
            return reduction * 0.70f + 0.30f;
        }

        void attackEntity(Entity& target) {
            int damage = baseDamage;
            target.takeDamage(damage);
            std::cout << "Enemy hits for " << damage << " damage!\n";
        }
    };

}