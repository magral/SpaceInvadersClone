#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "Enemy.h"

Enemy::Enemy(RECT* pos, HDC hdc) {
	healthManager = new HealthManager(maxHealth);
	HBITMAP image = (HBITMAP)LoadImage(NULL, "../Assets/enemy.bmp", IMAGE_BITMAP, 16, 16, LR_LOADFROMFILE);
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

Collider* Enemy::getCollider() {
	return collider;
}

Enemy::~Enemy() {
	delete(healthManager);
	delete(collider);
}
