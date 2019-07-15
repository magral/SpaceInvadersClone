#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include "Bullet.h"
#include "../Systems/Rect.h"

Bullet::Bullet(RECT* startingPosition, HDC hdc) {
	currentPosition = startingPosition;
	this->brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "../Assets/bullet.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	this->solidBrush = CreateSolidBrush(RGB(12, 12, 12));
	this->hdc = hdc;
	FillRect(hdc, currentPosition, this->brush);
}

void Bullet::move() {
	time_t oldTime = time(nullptr);
	while (currentPosition->top > 0) {
		time_t newTime = time(nullptr);
		if (difftime(newTime, oldTime) >= .1l) {
			paintBullet();
			oldTime = newTime;
		}
	}

}

void Bullet::paintBullet() {
	//TODO: figure out how to only unpaint the bullet
	FillRect(this->hdc, currentPosition, solidBrush);
	currentPosition->bottom -= 16;
	currentPosition->top -= 16;
	FillRect(this->hdc, currentPosition, brush);
}

Bullet::~Bullet() {
	delete(collider);
}