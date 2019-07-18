#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>

#include "./Systems/HealthManager.h"
#include "Player.h"
#include "../Objects/Bullet.h"
	
Player::Player(HDC hdc) {

	//TODO: Make some consts for starting position.
	this->position = new RECT { 320, 352, 352, 320 };
	HBITMAP image = (HBITMAP)LoadImage(NULL, "../Assets/ship.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	this->brush = CreatePatternBrush(image);
	this->solidBrush = CreateSolidBrush(RGB(12, 12, 12));
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
	Bullet* bullet = new Bullet(new RECT{ position->left + bulletWidthBuffer, position->top - playerSize, position->right - bulletWidthBuffer, position->bottom - bulletHeight}, hdc);
	bullets.push_back(bullet);
}

void Player::moveBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->move();
	}
}

void Player::processInput() {
	if (_kbhit() != 0) {
		switch (int c = _getch()) {
		case KEY_RIGHT:
			FillRect(this->hdc, position, solidBrush);
			position->left += playerSize;
			position->right += playerSize;
			FillRect(this->hdc, position, brush);
			break;

		case KEY_LEFT:
			FillRect(this->hdc, position, solidBrush);
			position->left -= playerSize;
			position->right -= playerSize;
			FillRect(this->hdc, position, brush);
			break;

		case KEY_SPACE:
			doAttack();
			break;

		default:
			return;
		}
	}
}

Player::~Player() {
	DeleteObject(this->brush);
	delete(healthManager);
	delete(collider);
}
