#pragma once
#include "character.h"
#include <fstream>
#include <sstream>   // ? potrzebne do istringstream
#include <cstring>   // ? dla strcpy_s
#include <set>

namespace structures {
	inline void saveGame(Character* character, int floor, int playerX, int playerY, Map* map, const char* filename = "save.txt") {
		std::ofstream out(filename);
		if (!out) {
			std::cerr << "Nie mozna zapisac gry!\n";
			return;
		}
		// zapisujemy dane gracza
		out << character->name << "\n";
		out << character->health << " " << character->mana << " " << floor << "\n";
		out << playerX << " " << playerY << "\n";
		out << (int)character->weapon.type << " " << character->weapon.attack << " " << character->weapon.hitChance << "\n";
		out << character->armor.armor << " " << character->armor.durability << "\n";

		std::set<Item*> zapisane;
		// zapisujemy przedmioty w ekwipunku
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				Item* item = character->inventory.getItem(x, y);
				if (item && zapisane.find(item) == zapisane.end()) {
					zapisane.insert(item);

					out << x << " " << y << " " << (int)item->type << " " << item->width << " " << item->height << " " << item->name;

					if (item->type == ItemType::Potion) {
						out << " " << item->healAmount << "\n";
					}
					else if (item->type == ItemType::Weapon) {
						out << " " << (int)item->weapon->type << " " << item->weapon->attack << " " << item->weapon->hitChance << "\n";
					}
					else if (item->type == ItemType::Armor) {
						out << " " << item->armor->armor << " " << item->armor->durability << "\n";
					}
				}
			}
		}
		// zapisujemy koniec listy przedmiotów
		out << "==ENDITEMS==\n";
		// zapisujemy mapê
		out << "==MAP==\n";
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				out << map->getTile(x, y); // np. '.', 'E', '#', 'I'
			}
			out << "\n";
		}

		out.close();
	}

	Character* loadGame(int& floor, int& playerX, int& playerY, Map* map, const char* filename = "save.txt") {
		std::ifstream in(filename);
		if (!in) {
			std::cerr << "Brak pliku zapisu.\n";
			return nullptr;
		}
		// Wczytujemy dane gracza
		std::string name;
		std::getline(in >> std::ws, name);
		int health, mana;
		in >> health >> mana >> floor;
		in >> playerX >> playerY;

		int wType, wAttack;
		float wHit;
		in >> wType >> wAttack >> wHit;

		int armorVal, durability;
		in >> armorVal >> durability;
		// tworzymy now¹ postaæ
		Character* c = new Character;
		c->name = name;
		c->health = health;
		c->mana = mana;
		c->baseArmor = 1;
		c->baseDamage = 5;
		c->armor = Armor{ armorVal, durability };
		c->weapon = Weapon{ (WeaponType)wType, wAttack, wHit };

		std::string line;
		while (std::getline(in, line)) {
			if (line == "==ENDITEMS==") break;

			std::istringstream iss(line);
			int x, y, type, width, height;
			std::string name;
			iss >> x >> y >> type >> width >> height >> name;

			Item* item = new Item;
			item->type = (ItemType)type;
			strcpy_s(item->name, name.c_str());
			item->width = width;
			item->height = height;

			if (item->type == ItemType::Potion) {
				iss >> item->healAmount;
				item->weapon = nullptr;
				item->armor = nullptr;
			}
			else if (item->type == ItemType::Weapon) {
				int wt, atk;
				float hit;
				iss >> wt >> atk >> hit;
				item->weapon = new Weapon{ (WeaponType)wt, atk, hit };
				item->armor = nullptr;
			}
			else if (item->type == ItemType::Armor) {
				int a, d;
				iss >> a >> d;
				item->armor = new Armor{ a, d };
				item->weapon = nullptr;
			}

			c->inventory.tryAddItem(item, x, y);
		}
		// Wczytujemy koniec listy przedmiotów
		while (std::getline(in, line)) {
			if (line == "==MAP==") break;
		}
		// Wczytujemy mapê
		for (int y = 0; y < 10; ++y) {
			std::getline(in, line);
			for (int x = 0; x < 10 && x < (int)line.length(); ++x) {
				map->setTile(x, y, line[x]);
			}
		}

		std::cout << "Gra wczytana.\n";
		return c;
	}
}
