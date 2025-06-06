#pragma once
#include <random>

namespace structures {

	enum class WeaponType {
		Sword,
		Axe,
		Dagger
	};

	struct Weapon {
		WeaponType type;
		int attack = 10;
		float hitChance;
	};

	Weapon generateWeapon(int level);

}