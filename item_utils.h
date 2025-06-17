#pragma once
#include "item.h"

namespace structures {

	inline const char* getItemName(Item* item) {
		if (!item) return "Brak";

		switch (item->type) {
		case ItemType::Potion:
			return "Potion";
		case ItemType::Weapon:
			switch (item->weapon->type) {
			case WeaponType::Sword: return "Sword";
			case WeaponType::Axe: return "Axe";
			case WeaponType::Dagger: return "Dagger";
			default: return "Weapon";
			}
		case ItemType::Armor:
			return "Armor";
		default:
			return "Nieznany";
		}
	}

}
