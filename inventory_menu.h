#pragma once
#include "character.h"
#include <iostream>
#include <cstring>
#include "item_utils.h"

namespace structures {

	void inspectItem(Item* item) {
		if (!item) {
			std::cout << "Brak przedmiotu.\n";
			return;
		}

		std::cout << "-- Szczegoly przedmiotu --\n";
		std::cout << "Nazwa: " << item->name << "\n";
		switch (item->type) {
		case ItemType::Potion:
			std::cout << "Typ: Potion\n";
			std::cout << "Leczy: " << item->healAmount << " HP\n";
			break;
		case ItemType::Weapon:
			std::cout << "Typ: Bron\n";
			std::cout << "Typ Broni: " << getItemName(item) << "\n";
			std::cout << "Atak: " << item->weapon->attack << "\n";
			std::cout << "Szansa trafienia: " << item->weapon->hitChance << "\n";
			break;
		case ItemType::Armor:
			std::cout << "Typ: Zbroja\n";
			std::cout << "Pancerz: " << item->armor->armor << "\n";
			std::cout << "Wytrzymalosc: " << item->armor->durability << " %\n";
			break;
		default:
			std::cout << "Nieznany typ\n";
		}
	}

	void inspectCharacter(Character* character) {
		std::cout << "====== Gracz ======\n";
		std::cout << "Imie: " << character->name << "\n";
		std::cout << "Zdrowie: " << character->health << "\n";
		std::cout << "Mana: " << character->mana << "\n";

		std::cout << "Bron: ";
		switch (character->weapon.type) {
		case WeaponType::Sword: std::cout << "Sword"; break;
		case WeaponType::Axe: std::cout << "Axe"; break;
		case WeaponType::Dagger: std::cout << "Dagger"; break;
		default: std::cout << "Nieznana"; break;
		}
		std::cout << " (Atak: " << character->weapon.attack << ", Hit: " << character->weapon.hitChance << ")\n";

		std::cout << "Zbroja: " << character->armor.armor << " pancerza, wytrzymalosc: " << character->armor.durability << "%\n\n";
	}

	void openInventoryMenu(Character* character) {
		system("cls");
		inspectCharacter(character);
		std::cout << "==== Ekwipunek ====" << std::endl;
		character->inventory.printInventory();

		std::string decyzja;
		std::cout << "(u)zyj, (i)nspekcja lub (x) wyjdz: ";
		std::cin >> decyzja;

		if (decyzja == "x") return;

		int x, y;
		std::cout << "Podaj wspolrzedne (x y): ";
		std::cin >> x >> y;

		if (decyzja == "u") {
			character->useItemAt(x, y);
			system("pause");
			openInventoryMenu(character);
		}
		else if (decyzja == "i") {
			inspectItem(character->inventory.getItem(x, y));
			system("pause");
			openInventoryMenu(character);
		}
		else {
			std::cout << "Nieznana opcja.\n";
			system("pause");
			openInventoryMenu(character);
		}
	}

}