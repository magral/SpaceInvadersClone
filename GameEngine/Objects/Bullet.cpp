#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include "Bullet.h"
#include "../Systems/Rect.h"

Bullet::Bullet(RECT* startingPosition, HDC hdc) {
	currentPosition = startingPosition;
	this->brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "../Assets/bullet.bmp", IMAGE_BITMAP, 4, 4, LR_LOADFROMFILE));
	this->solidBrush = CreateSolidBrush(RGB(12, 12, 12));
	this->hdc = hdc;
	FillRect(hdc, currentPosition, this->brush);
}

void Bullet::move() {
	paintBullet();	
}

void Bullet::paintBullet() {
	FillRect(this->hdc, currentPosition, solidBrush);
	currentPosition->bottom -= 4;
	currentPosition->top -= 4;
	FillRect(this->hdc, currentPosition, brush);
}

Bullet::~Bullet() {
	delete(collider);
}