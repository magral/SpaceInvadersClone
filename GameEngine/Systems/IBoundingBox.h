#pragma once
#include "BoundingBox.h"

struct BoundingBox;

class IBoundingBox {
public:

	virtual ~IBoundingBox() = default;
	virtual BoundingBox getBoundingBox() const = 0;
};