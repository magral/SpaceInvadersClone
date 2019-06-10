#pragma once

class HealthManager {
private:
	int maxHealth;
	int currentHealth;
public:
	HealthManager(int max);
	int adjustHealth(int delta);
	int getCurrentHealth();
	int getMaxHealth();
};
