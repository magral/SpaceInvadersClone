#pragma once
#include "HealthManager.h"
#include "Subject.h"

class Enemy : Subject{
private:
	HealthManager* healthManager;
	void notify();
	void onDeath();
public:
	Enemy(int level, int spawnX, int spawnY);
	HealthManager* getHealthManager();
};