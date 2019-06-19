
#include "Collision.h"

Collision::Collision() {

}

bool Collision::checkCollision(Collider* collider1, Collider* collider2) {
	Rect<int>* rect1 = collider1->getRect();
	Rect<int>* rect2 = collider2->getRect();

	int width1 = collider1->getRect()->getWidth();
	int width2 = collider2->getRect()->getWidth();

	int height1 = rect1->getHeight() - rect1->getHeight();
	int height2 = rect2->getHeight() - rect2->getHeight();

	if(rect1->getX() < (rect2->getX() + width2) &&
		(rect1->getX() + width1) > rect2->getX() &&
		rect1->getY() < (rect2->getY() + height2) &&
		(rect1->getY() + rect1->getHeight()) > rect2->getY())
	{
		return true;
	}
}