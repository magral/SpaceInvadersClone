#pragma once

#include <iostream>
#include <vector>

#include "../Characters/Systems/Collider.h"
class Collision {
private:
	//std::vector<Collider*> colliders;
public:
	Collision();
	bool checkCollision(Collider* collider1, Collider* collider2) const;
};