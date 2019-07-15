#pragma once
#include <Windows.h>

#include "../Characters/Systems/Collider.h"
#include "../Systems/Rect.h"

class Bullet {
private:
	Collider* collider;
	RECT* currentPosition;
	HBRUSH brush;
	HBRUSH solidBrush;
	HDC hdc;
	void paintBullet();
public:
	Bullet(RECT* startingPosition, HDC hdc);
	Collider* getCollider();
	void move();
	~Bullet();
};