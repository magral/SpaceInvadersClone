#pragma once
#include <Windows.h>
#include <conio.h>

#include "./Systems/HealthManager.h"
#include "../Events/Subject.h"
#include "../Systems/IBoundingBox.h"
#include "../Systems/BoundingBox.h"
#include "../Systems/BoundingTree.h"

class Enemy : public IBoundingBox {
private:
	HealthManager* healthManager;
	BoundingBox* collider;
	BoundingTree* collisionTree;
	HBRUSH brush;
	HBRUSH solidBrush;
	RECT* position;
	HDC hdc;
	
	void onDeath();
	const int maxHealth = 100;
public:
	Enemy(RECT* pos, HDC hdc, BoundingTree* tree);
	HealthManager* getHealthManager();
	void checkCurrentStatus();
	void notify();
	BoundingBox getBoundingBox() const;
	~Enemy();
};