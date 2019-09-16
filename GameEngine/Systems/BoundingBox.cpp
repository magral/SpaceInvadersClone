#include <algorithm>

#include "BoundingBox.h"

BoundingBox::BoundingBox() {
	minX = 0;
	minY = 0;
	maxX = 0;
	maxY = 0;
	surfaceArea = 0;
}

BoundingBox::BoundingBox(float minx, float miny, float maxx, float maxy) {
	minX = minx;
	minY = miny;
	maxX = maxx;
	maxY = maxy;
	surfaceArea = getSurfaceArea();
}

float BoundingBox::getSurfaceArea() const {
	return 2.0f * (getWidth() * getHeight() + getWidth() + getHeight());
}

float BoundingBox::getWidth() const {
	return maxX - minX;
}

float BoundingBox::getHeight() const{
	return maxY - minY;
}

bool BoundingBox::overlaps(const BoundingBox& other) const {
	return maxX > other.minX &&
		minX < other.maxX &&
		maxY > other.minY &&
		minY < other.maxY;
}

bool BoundingBox::contains(const BoundingBox& other) const {
	return other.minX >= minX &&
		other.maxX <= maxX &&
		other.minY >= minY &&
		other.maxY <= maxY;
}

BoundingBox BoundingBox::merge(const BoundingBox& other) const {
	return BoundingBox(
		std::min(minX, other.minX), std::min(minY, other.minY),
		std::max(maxX, other.maxX), std::max(maxY, other.maxY)
	);
}

BoundingBox BoundingBox::intersection(const BoundingBox& other) const {
	return BoundingBox(
		std::max(minX, other.minX), std::max(minY, other.minY),
		std::min(maxX, other.maxX), std::min(maxY, other.maxY)
	);
}