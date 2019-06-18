#include "Bullet.h"
#include "../Systems/Rect.h"

Bullet::Bullet(Rect<int>* startingPosition) {
	currentPosition = startingPosition;
}

Bullet::~Bullet() {
	delete(collider);
}