#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "./Systems/HealthManager.h"
#include "Player.h"
#include "../Objects/Bullet.h"
	
Player::Player(HDC hdc) {

	//TODO: Make some consts for starting position.
	this->position = new RECT { 320, 352, 352, 320 };
	this->brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "../Assets/ship.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	this->hdc = hdc;
	FillRect(hdc, position, this->brush);
	healthManager = new HealthManager(100);
}

HealthManager* Player::getHealthManager() {
	return healthManager;
}

Collider* Player::getCollider() {
	return collider;
}

void Player::doAttack() {
	// Create bullet and launch towards enemies
	Bullet* bullet = new Bullet(position);
}

void Player::processInput() {
	int input;
	while (true) {
		switch (int c = _getch()) {
		case KEY_RIGHT:
			position->left += 32;
			position->right += 32;
			system("cls");
			FillRect(this->hdc, position, brush);
			break;
		case KEY_LEFT:
			position->left -= 32;
			position->right -= 32;
			system("cls");
			FillRect(this->hdc, position, brush);
			break;

		case KEY_SPACE:
			doAttack();
			break;
		}
	}

	
}

Player::~Player() {
	DeleteObject(this->brush);
	delete(healthManager);
	delete(collider);
}
