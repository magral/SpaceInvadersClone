#pragma once
#include <Windows.h>

#include "../Characters/Systems/Collider.h"
#include "../Systems/Rect.h"
#include "../Systems/IBoundingBox.h"
#include "../Systems/BoundingBox.h"

class Bullet : public IBoundingBox {
private:
	BoundingBox* collider;
	RECT* currentPosition;
	HBRUSH brush;
	HBRUSH solidBrush;
	HDC hdc;
	void paintBullet();
public:
	Bullet(RECT* startingPosition, HDC hdc);
	BoundingBox getBoundingBox() const;
	void move();
	~Bullet();
};