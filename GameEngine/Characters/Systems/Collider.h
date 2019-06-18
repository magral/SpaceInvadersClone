#pragma once

#include "../../Systems/Rect.h"

struct Collider {
private:
	Rect<int>* rect;
public:
	Collider(Rect<int>* currentPosition, int height, int length);
	Collider(Rect<int>* currentPosition);
	~Collider();
};