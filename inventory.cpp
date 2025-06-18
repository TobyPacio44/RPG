#include "inventory.h"
#include <iostream>

namespace structures {

	Inventory::Inventory(int w, int h) : width(w), height(h) {
		grid.resize(height, std::vector<Item*>(width, nullptr));
	}

	bool Inventory::canPlace(Item* item, int x, int y) const {
		// Sprawdza, czy item zmieœci siê w danym miejscu siatki
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
					std::cout << "Item added to inventory at: " << i << ", " << j << "\n";
					return true;
				}
			}
		}

		std::cout << "Can't add to inventory, no space.\n";
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
		// Usuwa przedmiot z siatki i zwalnia pamiêæ (w tym jego weapon/armor)

		Item* item = grid[y][x];
		if (item == nullptr) return;

		// zerujemy wszystkie pola, ¿eby potem nie wisia³y wskaŸniki
		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
				if (grid[j][i] == item) {
					grid[j][i] = nullptr;
				}
			}
		}

		// zwalniamy pod-obiekty:
		delete item->weapon;
		delete item->armor;
		// na wszelki wypadek:
		item->weapon = nullptr;
		item->armor = nullptr;

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