#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include "Bullet.h"
#include "../Systems/Rect.h"
#include "../Systems/BoundingBox.h"

Bullet::Bullet(RECT* startingPosition, HDC hdc) {
	currentPosition = startingPosition;
	collider = new BoundingBox(startingPosition->left, startingPosition->bottom, startingPosition->right, startingPosition->top);
	this->brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "../Assets/bullet.bmp", IMAGE_BITMAP, 4, 4, LR_LOADFROMFILE));
	this->solidBrush = CreateSolidBrush(RGB(12, 12, 12));
	this->hdc = hdc;
	FillRect(hdc, currentPosition, this->brush);
}

void Bullet::move() {
	paintBullet();
	collider->maxY -= 4;
	collider->minY -= 4;
}

void Bullet::paintBullet() {
	FillRect(this->hdc, currentPosition, solidBrush);
	currentPosition->bottom -= 4;
	currentPosition->top -= 4;
	FillRect(this->hdc, currentPosition, brush);
}

BoundingBox Bullet::getBoundingBox() const {
	return *collider;
}

Bullet::~Bullet() {
	FillRect(this->hdc, currentPosition, solidBrush);
	delete(collider);
	delete(currentPosition);
}