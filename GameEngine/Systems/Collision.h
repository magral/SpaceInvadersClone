#pragma once

#include <iostream>
#include <vector>

#include "../Characters/Systems/Collider.h"
class Collision {
private:
	//std::vector<Collider*> colliders;
    // you started creating a vector of colliders here if these just had a callback for what happens when it is 
    // collided with then you can just loop over the colliders
public:
	Collision();
	bool checkCollision(Collider* collider1, Collider* collider2) const;
};