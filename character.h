#pragma once
#include <iostream>
#include <string>

#include "entity.h"
#include "weapon.h"
#include "armor.h"
#include "inventory.h"

namespace structures {

    struct Character : public Entity {

        Weapon weapon;
        Armor armor;
        Inventory inventory;

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

        float getArmorReduction(int armor) {
            if (armor <= 0) return 1.0f;
            if (armor >= 100) return 0.30f; // minimalnie 15% obrazen

            float logBase = log(101.0f); // maksymalny armor +1
            float reduction = 1.0f - (log((float)(armor + 1)) / logBase);
            return reduction * 0.70f + 0.30f; // skalowanie do 15% minimalnych obrazen
        }

        void takeDamage(int damage) override {
            if (armor.durability > 0) {
                float reductionFactor = getArmorReduction(armor.armor);
                int reducedDamage = (int)(damage * reductionFactor);
                if (reducedDamage <= 0) reducedDamage = 1; // nie ujemne obrazenia

                // Logarytmiczne zuzycie pancerza
                int wear = (int)(log((float)(reducedDamage + 1)) * 3);
                armor.durability -= wear;

                if (armor.durability >= 0) {
                    std::cout << name << " takes " << reducedDamage << " damage after armor reduction!\n";
                }
                else {
                    std::cout << name << "'s armor broke!\n";
                    armor.durability = 0;
                    armor.armor = 0;
                }
				Entity::takeDamage(reducedDamage);
			}
			else {
				std::cout << name << " has no armor left!\n";
				Entity::takeDamage(damage);
            }

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

        void useItemAt(int x, int y) {
            auto item = inventory.getItem(x, y);
            if (!item) {
                std::cout << "Brak przedmiotu na tej pozycji!\n";
                return;
            }

            if (item->type == ItemType::Potion) {
                std::cout << name << " uzywa " << item->name << " i leczy " << item->healAmount << " HP!\n";
                health += item->healAmount;
                inventory.removeItem(x, y);
            }

			if (item->type == ItemType::Weapon) {
                std::cout << name << " zmienia bron na " << item->name << "!\n";

                Item* oldWeaponItem = new Item;
				oldWeaponItem->type = ItemType::Weapon;
				oldWeaponItem->weapon = new Weapon(weapon);
				oldWeaponItem->width = item->width;
				oldWeaponItem->height = item->height;
                strcpy_s(oldWeaponItem->name, item->name);


				weapon = *item->weapon;
				inventory.removeItem(x, y);
                inventory.tryAddItem(oldWeaponItem, x, y);
			}

            if (item->type == ItemType::Armor) {
                std::cout << name << " zmienia Armor na " << item->name << "!\n";

                Item* oldArmorItem = new Item;
                oldArmorItem->type = ItemType::Armor;
                oldArmorItem->armor = new Armor(armor);
                oldArmorItem->width = item->width;
                oldArmorItem->height = item->height;
                strcpy_s(oldArmorItem->name, item->name);


                armor = *item->armor;
                inventory.removeItem(x, y);
                inventory.tryAddItem(oldArmorItem, x, y);
            }
          
        }
    };

}