#include "inventory.h"
#include <iostream>

namespace structures {

	Inventory::Inventory(int w, int h) : width(w), height(h) {
		for (int y = 0; y < 10; ++y)
			for (int x = 0; x < 10; ++x)
				grid[y][x] = nullptr;
	}

	bool Inventory::canPlace(Item* item, int x, int y) const {
		if (x + item->width > width || y + item->height > height)
			return false;

		for (int dy = 0; dy < item->height; ++dy) {
			for (int dx = 0; dx < item->width; ++dx) {
				if (grid[y + dy][x + dx] != nullptr)
					return false;
			}
		}
		return true;
	}

	bool Inventory::tryAddItem(Item* item, int x, int y) {
		if (addItem(item, x, y)) return true;

		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
				if (canPlace(item, i, j)) {
					addItem(item, i, j);
					std::cout << "Przedmiot dodany do ekwipunku na pozycji: " << i << ", " << j << "\n";
					return true;
				}
			}
		}

		std::cout << "Nie mozna dodac przedmiotu do ekwipunku, brak miejsca.\n";
		delete item;
		return false;
	}

	bool Inventory::addItem(Item* item, int x, int y) {
		if (!canPlace(item, x, y)) return false;

		for (int dy = 0; dy < item->height; ++dy) {
			for (int dx = 0; dx < item->width; ++dx) {
				grid[y + dy][x + dx] = item;
			}
		}
		return true;
	}

	void Inventory::removeItem(int x, int y) {
		Item* item = grid[y][x];
		if (item == nullptr) return;

		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
				if (grid[j][i] == item) {
					grid[j][i] = nullptr;
				}
			}
		}
		delete item;
	}

	Item* Inventory::getItem(int x, int y) {
		return grid[y][x];
	}

	void Inventory::printInventory() const {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Item* current = grid[y][x];

				if (current == nullptr) {
					std::cout << ". ";
					continue;
				}

				bool isTopLeft = true;
				if (y > 0 && grid[y - 1][x] == current) isTopLeft = false;
				if (x > 0 && grid[y][x - 1] == current) isTopLeft = false;

				if (isTopLeft) {
					switch (current->type) {
					case ItemType::Weapon: std::cout << "W "; break;
					case ItemType::Armor:  std::cout << "A "; break;
					case ItemType::Potion: std::cout << "P "; break;
					default:               std::cout << "? "; break;
					}
				}
				else {
					switch (current->type) {
					case ItemType::Weapon: std::cout << "w "; break;
					case ItemType::Armor:  std::cout << "a "; break;
					case ItemType::Potion: std::cout << "p "; break;
					default:               std::cout << ". "; break;
					}
				}
			}
			std::cout << '\n';
		}
	}


}