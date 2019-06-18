#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "./Systems/HealthManager.h"
#include "Player.h"
	
Player::Player(HDC hdc) {

	//TODO: Make some consts for starting position.
	this->position = { 320, 352, 352, 320 };
	this->brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "../Assets/ship.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	this->hdc = hdc;
	FillRect(hdc, &this->position, this->brush);
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
}

void Player::processInput() {
	int input;
	while (true) {
		switch (int c = _getch()) {
		case KEY_RIGHT:
			this->position.left += 32;
			this->position.right += 32;
			system("cls");
			FillRect(this->hdc, &this->position, brush);
			break;
		case KEY_LEFT:
			this->position.left -= 32;
			this->position.right -= 32;
			system("cls");
			FillRect(this->hdc, &this->position, brush);
			break;

		case KEY_SPACE:
			this->position.left -= 32;
			this->position.right -= 32;
			system("cls");
			FillRect(this->hdc, &this->position, brush);
			break;
		}
	}

	
}

Player::~Player() {
	DeleteObject(this->brush);
	delete(healthManager);
	delete(collider);
}
