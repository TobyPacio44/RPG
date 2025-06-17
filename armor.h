#pragma once
#include <random>

namespace structures {

	struct Armor {
		int armor;
		int durability;
	};

	Armor generateArmor(int level);
}