#pragma once

#include "../../Systems/Rect.h"

struct Collider {
private:
	Rect<int>* rect;
public:
	Collider(int x, int y, int height, int width);
	Collider(Rect<int>* currentPosition);
	Rect<int>* getRect();
	~Collider();
};