#pragma once
#include "weapon.h"
#include "armor.h"

namespace structures {

	enum class ItemType {
		Weapon,
		Armor,
		Potion
	};

	struct Item {
		ItemType type;
		char name[32];

		int width;
		int height;
		int healAmount = 0;

		Weapon* weapon;
		Armor* armor;
	};
}