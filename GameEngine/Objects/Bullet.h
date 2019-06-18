#pragma once

#include "../Characters/Systems/Collider.h"
#include "../Systems/Rect.h"

class Bullet {
private:
	Collider* collider;
	Rect<int>* currentPosition;

public:
	Bullet(Rect<int>* startingPosition);
	Collider* getCollider();
	void moveTowards(Rect<int> position);
	~Bullet();
};