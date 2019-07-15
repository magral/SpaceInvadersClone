#pragma once
#include <Windows.h>
#include <conio.h>

#include "./Systems/HealthManager.h"
#include "./Systems/Collider.h"

#ifndef PLAYER_H_
#define PLAYER_H_

enum Keys {
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_SPACE = 64,
};

class Player {
private:
	HealthManager* healthManager;
	Collider* collider;
	void doAttack();
	HBRUSH brush;
	RECT* position;
	HDC hdc;

public:
	Player(HDC hdc);
	HealthManager* getHealthManager();
	Collider* getCollider();
	void processInput();
	~Player();
};

#endif /*PLAYER_H_*/