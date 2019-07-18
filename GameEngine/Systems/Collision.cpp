
#include "Collision.h"

Collision::Collision() {

}

bool Collision::checkCollision(Collider* collider1, Collider* collider2) const { // const tells us that this function will not mess with anything
	Rect<int>* rect1 = collider1->getRect();
	Rect<int>* rect2 = collider2->getRect();

	const int width1 = collider1->getRect()->getWidth();
	const int width2 = collider2->getRect()->getWidth();

	const int height1 = rect1->getHeight() - rect1->getHeight(); // always 0
	const int height2 = rect2->getHeight() - rect2->getHeight(); // always 0 // unused

	if  (rect1->getX() < (rect2->getX() + width2) &&
		(rect1->getX() + width1) > rect2->getX() &&
		(rect1->getY() < (rect2->getY() + height2)) &&
		(rect1->getY() + rect1->getHeight()) > rect2->getY())
	{
		return true;
	}
	return false;
}