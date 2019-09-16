#pragma once
#include "BoundingBox.h"
#include "IBoundingBox.h"

#include <vector>
#include <map>
#include <list>

#define NULL_NODE_ADDRESS 0xffffffff

struct BoundingBoxNode {
	BoundingBox box;
	IBoundingBox* object;
	unsigned parentIndex;
	unsigned leftIndex;
	unsigned rightIndex;
	unsigned nextIndex;
	bool isLeaf() const;
	BoundingBoxNode() : object(nullptr), parentIndex(NULL_NODE_ADDRESS), leftIndex(NULL_NODE_ADDRESS), rightIndex(NULL_NODE_ADDRESS), nextIndex(NULL_NODE_ADDRESS)
	{

	}
};

class BoundingTree {
private:
	std::map<IBoundingBox*, unsigned> objectMap;
	std::vector<BoundingBoxNode> nodes;
	unsigned rootIndex;
	unsigned allocatedCount;
	unsigned nextFreeNode;
	unsigned nodeCapacity;
	unsigned growthSize;

	unsigned allocateNode();
	void deallocateNode(unsigned nodeIndex);
	void insertLeaf(unsigned leafNodeIndex);
	void removeLeaf(unsigned leafNodeIndex);
	void updateLeaf(unsigned leafNodeIndex, const BoundingBox& newBoundingBox);
	void fixUpwardsTree(unsigned treeNodeIndex);

public:
	BoundingTree(unsigned initialSize);
	~BoundingTree();

	void insertObject(IBoundingBox*& object);
	void removeObject(IBoundingBox*& object);
	void updateObject(IBoundingBox*& object);
	std::list<IBoundingBox*> queryOverlaps(IBoundingBox*& object) const;

};