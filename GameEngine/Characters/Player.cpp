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
	this->brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "../Assets/ship.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
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
	Bullet* bullet = new Bullet(new RECT{ position->left, position->top - 32, position->right, position->bottom - 32}, hdc);
	std::thread bulletThread(&Bullet::move, bullet);
	bulletThread.detach();
}

void Player::processInput() {
	while (true) {
		switch (int c = _getch()) {
		case KEY_RIGHT:
			FillRect(this->hdc, position, solidBrush);
			position->left += 32;
			position->right += 32;
			FillRect(this->hdc, position, brush);
			break;
		case KEY_LEFT:
			FillRect(this->hdc, position, solidBrush);
			position->left -= 32;
			position->right -= 32;
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
