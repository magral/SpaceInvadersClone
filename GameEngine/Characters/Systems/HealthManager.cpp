#include <iostream>

#include "HealthManager.h"

int maxHealth;
int currentHealth; 

HealthManager::HealthManager(int max) {
	maxHealth = max;
	currentHealth = max;
}

int HealthManager::adjustHealth(int delta) {
	currentHealth += delta;
	std::cout << currentHealth;
	return currentHealth;
}

int HealthManager::getCurrentHealth() {
	return currentHealth;
}

int HealthManager::getMaxHealth() {
	return maxHealth;
}