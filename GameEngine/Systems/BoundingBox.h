#pragma once
#include "IBoundingBox.h"

struct BoundingBox
{
private: 
	float getSurfaceArea() const;

public: 
	float minX;
	float minY;
	float maxX;
	float maxY;
	float z = 1.0;
	float surfaceArea;

	BoundingBox();
	BoundingBox(float minx, float miny, float maxx, float maxy);
	bool overlaps(const BoundingBox& other) const;
	bool contains(const BoundingBox& other) const;
	BoundingBox merge(const BoundingBox& other) const;
	BoundingBox intersection(const BoundingBox& other) const;

	float getWidth() const;
	float getHeight() const;

};