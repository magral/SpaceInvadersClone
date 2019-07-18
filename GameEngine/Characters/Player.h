#pragma once
#include <Windows.h>
#include <conio.h>
#include <vector>

#include "./Systems/HealthManager.h"
#include "./Systems/Collider.h"
#include "../Objects/Bullet.h"

#ifndef PLAYER_H_
#define PLAYER_H_

enum Keys {
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_SPACE = ' ',
};

class Player {
private:
	HealthManager* healthManager;
	Collider* collider;
	void doAttack();
	HBRUSH brush;
	HBRUSH solidBrush;
	RECT* position;
	HDC hdc;
	std::vector<Bullet*> bullets;

	const int playerSize = 32;
	const int bulletWidthBuffer = 14;
	const int bulletHeight = 4;

public:
	Player(HDC hdc);
	HealthManager* getHealthManager();
	Collider* getCollider();
	void processInput();
	void moveBullets();
	~Player();
};

#endif /*PLAYER_H_*/