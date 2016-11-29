#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Math.h"
#include <vector>
#include <list>

class GameObject;


class QuadtreeNode
{
public:
	QuadtreeNode() {}
	QuadtreeNode(math::AABB &_box);
	~QuadtreeNode();
	bool Create(math::AABB box);
	bool Clear();
	bool Insert(GameObject* go);
	bool Remove(GameObject* go);
	void Divide();

	template<typename TYPE>
	inline void Intersect(std::vector<GameObject*> &go, const TYPE &primitive);
	math::AABB box;
private:
	QuadtreeNode* parent = nullptr;
	std::vector<QuadtreeNode*> childs;
	std::list<GameObject*> objects;
	
};





class Quadtree
{
public:
	Quadtree(){}
	Quadtree(math::AABB box);
	~Quadtree();

	QuadtreeNode* root;
private:
	
};

template<typename TYPE>
inline void QuadtreeNode::Intersect(std::vector<GameObject*> &go, const TYPE &primitive)
{
	if (primitive.Intersects(box))
	{
		for (std::list<GameObject*>::const_iterator it = this->objects.begin(); it != this->objects.end(); ++it)
		{
			if (primitive.Intersects((*it)->transform->GetAABB()))
				go.push_back(*it);
		}
		for (int i = 0; i < 4; ++i)
			if (childs[i] != nullptr) childs[i]->Intersect(go, primitive);
	}
}

#endif // !__QUADTREE_H__

