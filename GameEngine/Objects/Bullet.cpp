#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include "Bullet.h"
#include "../Systems/Rect.h"

Bullet::Bullet(RECT* startingPosition, HDC hdc) {
	currentPosition = startingPosition;
	this->brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "../Assets/bullet.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	this->solidBrush = CreateSolidBrush(RGB(12, 12, 12)); // majik
	this->hdc = hdc;
	FillRect(hdc, currentPosition, this->brush);
}

void Bullet::move() {
	time_t oldTime = time(nullptr);
	while (currentPosition->top > 0) {
		time_t newTime = time(nullptr);
		if (difftime(newTime, oldTime) >= .1) { // majik number 
			paintBullet();
			oldTime = newTime;
		}
        // this is an infinite loop
        // please add a sleep
        // without this loop this program was maxing out the CPU
        // with this sleep the cpu usage as ~0%
        Sleep(100);
	}
	delete(this);
}

void Bullet::paintBullet() {
	FillRect(this->hdc, currentPosition, solidBrush);
	currentPosition->bottom -= 16; // majik numbers please use a kHeight constant or similar
	currentPosition->top -= 16; // same
	FillRect(this->hdc, currentPosition, brush);
}

Bullet::~Bullet() {
	delete(collider);
}