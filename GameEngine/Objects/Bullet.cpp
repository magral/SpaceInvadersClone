#include <conio.h>

#include "Bullet.h"
#include "../Systems/Rect.h"

Bullet::Bullet(RECT* startingPosition) {
	currentPosition = startingPosition;
}

Bullet::~Bullet() {
	delete(collider);
}