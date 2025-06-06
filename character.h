#pragma once
#include "entity.h"
#include "weapon.h"
#include "armor.h"
#include <string>
#include <iostream>

namespace structures {

    struct Character : public Entity {
        Weapon weapon;
        Armor armor;

        void fightEnemy(Character& enemy) {
            float roll = static_cast<float>(rand()) / RAND_MAX;  // losowa liczba 0..1
            if (roll <= weapon.hitChance) {
                int totalDamage = baseDamage + weapon.attack;
                enemy.takeDamage(totalDamage);
                std::cout << name << " hits for " << totalDamage << " damage!\n";
            }
            else {
                std::cout << name << " missed the attack!\n";
            }
        }

        void takeDamage(int damage) override {
            damage -= armor.armor;
            Entity::takeDamage(damage);  // wywo³ujemy bazow¹ metodê
        }

        static Character generateCharacter(const std::string& Name, int level) {
            Character current;
            current.health = 100;
            current.name = Name;
            current.weapon = generateWeapon(level);
            current.armor = generateArmor(level);
            current.baseArmor = 1;
            current.baseDamage = 5;
            current.mana = 20;
            return current;
        }
    };

}