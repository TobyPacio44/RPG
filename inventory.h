#pragma once
#include "item.h"
#include <vector>
#include <memory>
#include <iostream>

namespace structures {
		
	class Inventory {
	public:
		Inventory(int width = 10, int height = 10);

		bool addItem(Item* item, int x, int y);
		bool tryAddItem(Item* item, int x, int y);
		void removeItem(int x, int y);
		void printInventory() const;

		Item* getItem(int x, int y);


	private:
		int width;
		int height;
		std::vector<std::vector<Item*>> grid;
		bool canPlace(Item* item, int x, int y) const;
	};


}