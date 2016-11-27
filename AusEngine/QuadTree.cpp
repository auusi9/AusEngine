#include "QuadTree.h"
#include "GameObject.h"

Quadtree::Quadtree()
{
}


Quadtree::~Quadtree()
{
}


QuadtreeNode::QuadtreeNode()
{
}

QuadtreeNode::~QuadtreeNode()
{
}

bool QuadtreeNode::Create(math::AABB box)
{
	return false;
}


bool QuadtreeNode::Clear()
{
	return false;
}

int QuadtreeNode::Insert(GameObject* go)
{
	return 0;
}

bool QuadtreeNode::Remove(GameObject* go)
{
	return false;
}

template<typename TYPE>
inline void QuadtreeNode::Intersect(std::vector<GameObject*> &go, const TYPE &primitive)
{
	return false;
}







