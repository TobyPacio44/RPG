#include "fight.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace structures {

	int calculateModifiedDamage(int baseDamage) {
		float variation = 0.8f + static_cast<float>(rand() % 41) / 100.0f; // 0.80 - 1.20
		return static_cast<int>(baseDamage * variation);
	}

	bool checkHit(float hitChance) {
		float roll = static_cast<float>(rand()) / RAND_MAX; // 0.0 - 1.0
		return roll <= hitChance;
	}

	bool checkCrit() {
		int chance = rand() % 100;
		return chance < 10; // 10% na krytyka
	}

	bool fightRound(Character& player, Enemy& enemy) {
		system("cls");

		std::cout << "Aktualne HP:\n" << player.name << ": " << player.health
			<< "\n" << enemy.name << ": " << enemy.health << "\n";

		std::cout << "\n=== Walka ===\n";

		// Atak gracza
		if (checkHit(player.weapon.hitChance)) {
			int damage = player.baseDamage + player.weapon.attack;
			damage = calculateModifiedDamage(damage);

			if (checkCrit()) {
				std::cout << "Trafienie krytyczne!\n";
				damage *= 2;
			}

			std::cout <<player.name << " trafia za " << damage << " obrazen.\n";
			enemy.takeDamage(damage);
		}
		else {
			std::cout << player.name << " chybia!\n";
		}

		if (enemy.health <= 0) {
			std::cout << enemy.name << " zostal pokonany!\n";
			return true;
		}

		Sleep(2000);

		// Atak przeciwnika
		int damage = calculateModifiedDamage(enemy.baseDamage);
		std::cout <<enemy.name << " trafia za " << damage << " obrazen.\n";
		player.takeDamage(damage);

		if (player.health <= 0) {
			std::cout << player.name << " zostal pokonany!\n";
			return true;
		}

		Sleep(2000);

		return false;
	}

}
