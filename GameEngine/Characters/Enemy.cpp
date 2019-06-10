#include <iostream>
#include "Enemy.h"

Enemy::Enemy(int level, int spawnX, int spawnY ) {
	healthManager = new HealthManager(level * 100);
}

HealthManager* Enemy::getHealthManager() {
	return healthManager;
}

void Enemy::notify() {
	std::cout << "update scoreboard" << std::endl;
}

void Enemy::onDeath() {
	//delete me
	notify();
}
