#pragma once
#include <Windows.h>
#include <conio.h>
#include <vector>

#include "./Systems/HealthManager.h"
#include "../Objects/Bullet.h"
#include "../Systems/BoundingTree.h"
#include "../Systems/BoundingBox.h"
#include "../Systems/IBoundingBox.h"

#ifndef PLAYER_H_
#define PLAYER_H_

enum Keys {
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_SPACE = ' ',
};

class Player : public IBoundingBox {
private:
	HealthManager* healthManager;
	BoundingBox* collider;
	BoundingTree* collisionTree;
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
	Player(HDC hdc, BoundingTree* tree);
	HealthManager* getHealthManager();
	BoundingBox getBoundingBox() const;
	void processInput();
	void moveBullets();
	~Player();
};

#endif /*PLAYER_H_*/