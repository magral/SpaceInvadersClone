
#include <stack>
#include <vector>

#include "BoundingTree.h"

BoundingTree::BoundingTree(unsigned size) {
	rootIndex = (NULL_NODE_ADDRESS);
	allocatedCount = 0;
	nextFreeNode = 0;
	nodeCapacity = size;
	growthSize = size;
	nodes.resize(size);

	for (unsigned nodeIndex = 0; nodeIndex < size; nodeIndex++) {
		BoundingBoxNode& node = nodes[nodeIndex];
		node.nextIndex = nodeIndex + 1;
	}

	nodes[size - 1].nextIndex = NULL_NODE_ADDRESS;
}

bool BoundingBoxNode::isLeaf() const {
	return leftIndex == NULL_NODE_ADDRESS;
}

BoundingTree::~BoundingTree() {

}

unsigned BoundingTree::allocateNode() {
	if (nextFreeNode == NULL_NODE_ADDRESS) {
		nodeCapacity += growthSize;
		nodes.resize(nodeCapacity);
		for (unsigned nodeIndex = allocatedCount; nodeIndex < nodeCapacity; nodeIndex++) {
			BoundingBoxNode& node = nodes[nodeIndex];
			node.nextIndex = nodeIndex + 1;
		}
		nodes[nodeCapacity - 1].nextIndex = NULL_NODE_ADDRESS;
		nextFreeNode = allocatedCount;
	}

	unsigned nodeIndex = nextFreeNode;
	BoundingBoxNode& allocatedNode = nodes[nodeIndex];
	allocatedNode.parentIndex = NULL_NODE_ADDRESS;
	allocatedNode.leftIndex = NULL_NODE_ADDRESS;
	allocatedNode.rightIndex = NULL_NODE_ADDRESS;
	nextFreeNode = allocatedNode.nextIndex;
	allocatedCount++;

	return nodeIndex;
}

void BoundingTree::deallocateNode(unsigned nodeIndex) {
	BoundingBoxNode& deallocatedNode = nodes[nodeIndex];
	deallocatedNode.nextIndex = nextFreeNode;
	nextFreeNode = nodeIndex;
	allocatedCount--;
}

void BoundingTree::insertObject(IBoundingBox*& object) {
	unsigned nodeIndex = allocateNode();
	BoundingBoxNode& node = nodes[nodeIndex];

	node.box = object->getBoundingBox();
	node.object = object;

	insertLeaf(nodeIndex);
	objectMap[object] = nodeIndex;

}

void BoundingTree::removeObject(IBoundingBox*& object) {
	unsigned nodeIndex = objectMap[object];
	removeLeaf(nodeIndex);
	deallocateNode(nodeIndex);
	objectMap.erase(object);
}

void BoundingTree::updateObject(IBoundingBox*& object) {
	unsigned nodeIndex = objectMap[object];
	updateLeaf(nodeIndex, object->getBoundingBox());
}

std::list<IBoundingBox*> BoundingTree::queryOverlaps(IBoundingBox*& object) const
{
	std::list<IBoundingBox*> overlaps;
	std::stack<unsigned> stack;
	BoundingBox testAabb = object->getBoundingBox();

	stack.push(rootIndex);
	while (!stack.empty())
	{
		unsigned nodeIndex = stack.top();
		stack.pop();

		if (nodeIndex == NULL_NODE_ADDRESS) continue;

		const BoundingBoxNode& node = nodes[nodeIndex];
		if (node.box.overlaps(testAabb))
		{
			if (node.isLeaf() && node.object != object)
			{
				overlaps.push_front(node.object);
			}
			else
			{
				stack.push(node.leftIndex);
				stack.push(node.rightIndex);
			}
		}
	}

	return overlaps;
}

void BoundingTree::insertLeaf(unsigned leafNodeIndex)
{

	// if the tree is empty then we make the root the leaf
	if (rootIndex == NULL_NODE_ADDRESS)
	{
		rootIndex = leafNodeIndex;
		return;
	}

	// search for the best place to put the new leaf in the tree
	// we use surface area and depth as search heuristics
	unsigned treeNodeIndex = rootIndex;
	BoundingBoxNode& leafNode = nodes[leafNodeIndex];
	while (!nodes[treeNodeIndex].isLeaf())
	{
		// because of the test in the while loop above we know we are never a leaf inside it
		const BoundingBoxNode& treeNode = nodes[treeNodeIndex];
		unsigned leftNodeIndex = treeNode.leftIndex;
		unsigned rightNodeIndex = treeNode.rightIndex;
		const BoundingBoxNode& leftNode = nodes[leftNodeIndex];
		const BoundingBoxNode& rightNode = nodes[rightNodeIndex];

		BoundingBox combinedAabb = treeNode.box.merge(leafNode.box);

		float newParentNodeCost = 2.0f * combinedAabb.surfaceArea;
		float minimumPushDownCost = 2.0f * (combinedAabb.surfaceArea - treeNode.box.surfaceArea);

		// use the costs to figure out whether to create a new parent here or descend
		float costLeft;
		float costRight;
		if (leftNode.isLeaf())
		{
			costLeft = leafNode.box.merge(leftNode.box).surfaceArea + minimumPushDownCost;
		}
		else
		{
			BoundingBox newLeftAabb = leafNode.box.merge(leftNode.box);
			costLeft = (newLeftAabb.surfaceArea - leftNode.box.surfaceArea) + minimumPushDownCost;
		}
		if (rightNode.isLeaf())
		{
			costRight = leafNode.box.merge(rightNode.box).surfaceArea + minimumPushDownCost;
		}
		else
		{
			BoundingBox newRightAabb = leafNode.box.merge(rightNode.box);
			costRight = (newRightAabb.surfaceArea - rightNode.box.surfaceArea) + minimumPushDownCost;
		}

		// if the cost of creating a new parent node here is less than descending in either direction then
		// we know we need to create a new parent node, errrr, here and attach the leaf to that
		if (newParentNodeCost < costLeft && newParentNodeCost < costRight)
		{
			break;
		}

		// otherwise descend in the cheapest direction
		if (costLeft < costRight)
		{
			treeNodeIndex = leftNodeIndex;
		}
		else
		{
			treeNodeIndex = rightNodeIndex;
		}
	}

	// the leafs sibling is going to be the node we found above and we are going to create a new
	// parent node and attach the leaf and this item
	unsigned leafSiblingIndex = treeNodeIndex;
	BoundingBoxNode& leafSibling = nodes[leafSiblingIndex];
	unsigned oldParentIndex = leafSibling.parentIndex;
	unsigned newParentIndex = allocateNode();
	BoundingBoxNode& newParent = nodes[newParentIndex];
	newParent.parentIndex = oldParentIndex;
	newParent.box = leafNode.box.merge(leafSibling.box); // the new parents aabb is the leaf aabb combined with it's siblings aabb
	newParent.leftIndex = leafSiblingIndex;
	newParent.rightIndex = leafNodeIndex;
	leafNode.parentIndex = newParentIndex;
	leafSibling.parentIndex = newParentIndex;

	if (oldParentIndex == NULL_NODE_ADDRESS)
	{
		// the old parent was the root and so this is now the root
		rootIndex = newParentIndex;
	}
	else
	{
		// the old parent was not the root and so we need to patch the left or right index to
		// point to the new node
		BoundingBoxNode& oldParent = nodes[oldParentIndex];
		if (oldParent.leftIndex == leafSiblingIndex)
		{
			oldParent.leftIndex = newParentIndex;
		}
		else
		{
			oldParent.rightIndex = newParentIndex;
		}
	}

	// finally we need to walk back up the tree fixing heights and areas
	treeNodeIndex = leafNode.parentIndex;
	fixUpwardsTree(treeNodeIndex);
}

void BoundingTree::removeLeaf(unsigned leafNodeIndex)
{
	// if the leaf is the root then we can just clear the root pointer and return
	if (leafNodeIndex == rootIndex)
	{
		rootIndex = NULL_NODE_ADDRESS;
		return;
	}

	BoundingBoxNode& leafNode = nodes[leafNodeIndex];
	unsigned parentNodeIndex = leafNode.parentIndex;
	const BoundingBoxNode& parentNode = nodes[parentNodeIndex];
	unsigned grandParentNodeIndex = parentNode.parentIndex;
	unsigned siblingNodeIndex = parentNode.leftIndex == leafNodeIndex ? parentNode.rightIndex : parentNode.leftIndex;
	BoundingBoxNode& siblingNode = nodes[siblingNodeIndex];

	if (grandParentNodeIndex != NULL_NODE_ADDRESS)
	{
		// if we have a grand parent (i.e. the parent is not the root) then destroy the parent and connect the sibling to the grandparent in its
		// place
		BoundingBoxNode& grandParentNode = nodes[grandParentNodeIndex];
		if (grandParentNode.leftIndex == parentNodeIndex)
		{
			grandParentNode.leftIndex = siblingNodeIndex;
		}
		else
		{
			grandParentNode.rightIndex = siblingNodeIndex;
		}
		siblingNode.parentIndex = grandParentNodeIndex;
		deallocateNode(parentNodeIndex);

		fixUpwardsTree(grandParentNodeIndex);
	}
	else
	{
		// if we have no grandparent then the parent is the root and so our sibling becomes the root and has it's parent removed
		rootIndex = siblingNodeIndex;
		siblingNode.parentIndex= NULL_NODE_ADDRESS;
		deallocateNode(parentNodeIndex);
	}

	leafNode.parentIndex = NULL_NODE_ADDRESS;
}

void BoundingTree::updateLeaf(unsigned leafNodeIndex, const BoundingBox& newAaab)
{
	BoundingBoxNode& node = nodes[leafNodeIndex];

	// if the node contains the new aabb then we just leave things
	// TODO: when we add velocity this check should kick in as often an update will lie within the velocity fattened initial aabb
	// to support this we might need to differentiate between velocity fattened aabb and actual aabb
	if (node.box.contains(newAaab)) return;

	removeLeaf(leafNodeIndex);
	node.box = newAaab;
	insertLeaf(leafNodeIndex);
}

void BoundingTree::fixUpwardsTree(unsigned treeNodeIndex)
{
	while (treeNodeIndex != NULL_NODE_ADDRESS)
	{
		BoundingBoxNode& treeNode = nodes[treeNodeIndex];

		// fix height and area
		const BoundingBoxNode& leftNode = nodes[treeNode.leftIndex];
		const BoundingBoxNode& rightNode = nodes[treeNode.rightIndex];
		treeNode.box = leftNode.box.merge(rightNode.box);

		treeNodeIndex = treeNode.parentIndex;
	}
}