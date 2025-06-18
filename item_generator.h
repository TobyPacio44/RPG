#pragma once
#include "item.h"
#include <cstdlib> // rand
#include <cstdio>  // sprintf
#include "item_utils.h"

namespace structures {

	Item* generatePotion(int level) {
		Item* potion = new Item;
		potion->type = ItemType::Potion;
		sprintf_s(potion->name, "Potion Lv%d", level);
		potion->width = 2;
		potion->height = 2;
		potion->healAmount = 10 + (rand() % (level * 10));
		potion->weapon = nullptr;
		potion->armor = nullptr;
		return potion;
	}

	Item* generateWeaponItem(int level) {
		Item* item = new Item;
		item->type = ItemType::Weapon;
		item->weapon = new Weapon(generateWeapon(level));

		const char* weaponName = getItemName(item);
		sprintf_s(item->name, "%s Lv%d", weaponName, level);

		item->width = 2;
		item->height = 4;
		item->healAmount = 0; // Brak leczenia dla broni
		item->armor = nullptr;
		return item;
	}

	Item* generateArmorItem(int level) {
		Item* item = new Item;
		item->type = ItemType::Armor;
		item->armor = new Armor(generateArmor(level));
		sprintf_s(item->name, "Armor Lv%d", level);
		item->width = 3;
		item->height = 4;
		item->healAmount = 0; // Brak leczenia dla zbroi
		item->weapon = nullptr;
		return item;
	}

	Item* generateRandomItem(int level) {
		int roll = rand() % 3; // 0 = potion, 1 = armor, 2 = weapon
		if (roll == 0) return generatePotion(level);
		if (roll == 1) return generateArmorItem(level);
		return generateWeaponItem(level);
	}

}
