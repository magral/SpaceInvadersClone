#pragma once
#include <Windows.h>
#include <conio.h>

#include "./Systems/HealthManager.h"
#include "../Events/Subject.h"
#include "Systems/Collider.h"

class Enemy : Subject{
private:
	HealthManager* healthManager;
	Collider* collider;
	HBRUSH brush;
	HBRUSH solidBrush;
	RECT* position;
	HDC hdc;
	void notify();
	void onDeath();
	const int maxHealth = 100;
public:
	Enemy(RECT* pos, HDC hdc);
	HealthManager* getHealthManager();
	Collider* getCollider();
	~Enemy();
};