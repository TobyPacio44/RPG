#pragma once
#include <random>

namespace structures {

	struct Armor {
		int armor;
		int durability;
		int fireDurability;
		int iceDurability;
	};

	Armor generateArmor(int level);
}