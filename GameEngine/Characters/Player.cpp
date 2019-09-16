#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "./Systems/HealthManager.h"
#include "Player.h"
#include "Enemy.h"
#include "../Objects/Bullet.h"
	
Player::Player(HDC hdc, BoundingTree* tree) {
	//TODO: Make some consts for starting position.
	this->position = new RECT { 320, 352, 352, 320 };
	collider = new BoundingBox(position->left, position->bottom, position->right, position->top);
	collisionTree = tree;
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

BoundingBox Player::getBoundingBox() const {
	return *collider;
}

void Player::doAttack() {
	// Create bullet and launch towards enemies
	Bullet* bullet = new Bullet(new RECT{ position->left + bulletWidthBuffer, position->top - playerSize, position->right - bulletWidthBuffer, position->bottom - bulletHeight}, hdc);
	IBoundingBox* box = static_cast<IBoundingBox*>(bullet);
	collisionTree->insertObject(box);
	bullets.push_back(bullet);
}

void Player::moveBullets() {
	if (bullets.size() == 0) {
		return;
	}
	std::list<IBoundingBox*> collisionList;
	int deleteIndex = -1;
	//move each bullet, then check for collision
	for (unsigned i = 0; i < bullets.size(); i++) {
		bullets[i]->move();
		IBoundingBox* bulletBox = static_cast<IBoundingBox*>(bullets[i]);
		collisionTree->updateObject(bulletBox);
		collisionList = collisionTree->queryOverlaps(bulletBox);
		std::list<IBoundingBox*>::iterator it = collisionList.begin();
		for (unsigned i = 0; i < collisionList.size(); i++) {
			Enemy* nemy = dynamic_cast<Enemy*>(*it);
			nemy->getHealthManager()->adjustHealth(-10);
			if (it._Getpnext() != NULL) {
				std::advance(it, 1);
			}
		}
		
		if (!collisionList.empty()) {
			collisionTree->removeObject(bulletBox);
			deleteIndex = i;
		}
	}
	// bullets should disappear if they made an impact
	if (deleteIndex >= 0) {
		
		delete(bullets[deleteIndex]);
		bullets.erase(bullets.begin() + deleteIndex);
	}
}

void Player::processInput() {
	if (_kbhit() != 0) {
		switch (int c = _getch()) {
		case KEY_RIGHT:
			FillRect(this->hdc, position, solidBrush);
			position->left += playerSize;
			position->right += playerSize;
			collider->maxX += playerSize;
			collider->minX += playerSize;
			FillRect(this->hdc, position, brush);
			break;

		case KEY_LEFT:
			FillRect(this->hdc, position, solidBrush);
			position->left -= playerSize;
			position->right -= playerSize;
			collider->minX -= playerSize;
			collider->maxX -= playerSize;
			FillRect(this->hdc, position, brush);
			break;

		case KEY_SPACE:
			doAttack();
			break;

		default:
			return;
		}
	}
	IBoundingBox* thisPlayer = static_cast<IBoundingBox*>(this);
	collisionTree->updateObject(thisPlayer);
}

Player::~Player() {
	DeleteObject(this->brush);
	delete(healthManager);
	delete(collider);
}
