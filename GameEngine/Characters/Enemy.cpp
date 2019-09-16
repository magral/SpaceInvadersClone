#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "Enemy.h"
#include "../Systems/IBoundingBox.h"
#include "../Systems/BoundingBox.h"
#include "../Systems/BoundingTree.h"

Enemy::Enemy(RECT* pos, HDC hdc, BoundingTree* tree) {
	healthManager = new HealthManager(100);

	collider = new BoundingBox(pos->left, pos->bottom, pos->right, pos->top);
	HBITMAP image = (HBITMAP)LoadImage(NULL, "../Assets/enemy.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	this->brush = CreatePatternBrush(image);
	this->solidBrush = CreateSolidBrush(RGB(12, 12, 12));
	this->position = pos;
	FillRect(hdc, position, this->brush);
	this->hdc = hdc;
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

void Enemy::checkCurrentStatus() {
	if (healthManager->getCurrentHealth() <= 0) {
		FillRect(hdc, position, this->solidBrush);
		IBoundingBox* box = static_cast<IBoundingBox*>(this);
		collisionTree->removeObject(box);
	}
	delete(this);
}

BoundingBox Enemy::getBoundingBox() const {
	return *collider;
}

Enemy::~Enemy() {
	delete(healthManager);
	delete(collider);
}
