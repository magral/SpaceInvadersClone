#pragma once
#include <Windows.h>

#include "../Characters/Systems/Collider.h"
#include "../Systems/Rect.h"

class Bullet {
private:
	Collider* collider;
	RECT* currentPosition;
	void moveTowards(Rect<int> position);
public:
	Bullet(RECT* startingPosition);
	Collider* getCollider();
	
	~Bullet();
};