#include "Collider.h"
#include "../../Systems/Rect.h"

Collider::Collider(int x, int y, int height, int width) {
	rect = new Rect<int>(x, y, height, width);
}

Collider::Collider(Rect<int>* currentPosition) {
	rect = new Rect<int>(currentPosition->getX(), currentPosition->getY(), currentPosition->getHeight(), currentPosition->getWidth());
}

Rect<int>* Collider::getRect() {
	return rect;
}

Collider::~Collider() {
	delete(rect);
}