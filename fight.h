#pragma once
#include "character.h"
#include "enemy.h"

namespace structures {

    bool fightRound(Character* player, Enemy* enemy, void (*enemyAttackFn)(Enemy*, Character*));
    void regularEnemyAttack(Enemy* enemy, Character* player);
    void bossEnemyAttack(Enemy* enemy, Character* player);
}