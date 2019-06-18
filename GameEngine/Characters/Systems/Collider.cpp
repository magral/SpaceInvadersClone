#include "Collider.h"
#include "../../Systems/Rect.h"

Collider::Collider(Rect<int>* currentPosition, int height, int length) {
	rect = new Rect<int>(currentPosition->getLeft(), currentPosition->getBottom() + height, currentPosition->getLeft() + length, currentPosition->getBottom());
}

Collider::Collider(Rect<int>* currentPosition) {
	rect = new Rect<int>(currentPosition->getLeft(), currentPosition->getTop(), currentPosition->getRight(), currentPosition->getBottom());
}

Collider::~Collider() {
	delete(rect);
}