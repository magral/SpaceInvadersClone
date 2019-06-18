#pragma once
#include "./Systems/HealthManager.h"
#include "../Events/Subject.h"
#include "Systems/Collider.h"

class Enemy : Subject{
private:
	HealthManager* healthManager;
	Collider* collider;
	void notify();
	void onDeath();
public:
	Enemy(int level, int spawnX, int spawnY);
	HealthManager* getHealthManager();
	Collider* getCollider();
	~Enemy();
};