#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Math.h"
#include <vector>
#include <list>

class GameObject;


class QuadtreeNode
{
public:
	QuadtreeNode() {};
	QuadtreeNode(math::AABB &_box);
	~QuadtreeNode();
	bool Create(math::AABB box);
	bool Clear();
	bool Insert(GameObject* go);
	bool Remove(GameObject* go);
	void Divide();

	template<typename TYPE>
	inline void Intersect(std::vector<GameObject*> &go, const TYPE &primitive);
	math::AABB box = math::AABB();

	void GetBoxes(std::vector<math::AABB> &box)
	{
		for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
		{
			(*item)->GetBoxes(box);
		}
		box.push_back(this->box);
	}
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

	QuadtreeNode* root = nullptr;

private:
	
};

template<typename TYPE>
inline void QuadtreeNode::Intersect(std::vector<GameObject*> &go, const TYPE &primitive)
{
	if (primitive.Intersects(box))
	{
		for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
		{
			(*item)->Intersect(go, primitive);
		}
		for (std::list<GameObject*>::const_iterator it = this->objects.begin(); it != this->objects.end(); ++it)
		{
			if (primitive.Intersects((*it)->transform->GetAABB()))
				go.push_back(*it);
		}

	}

}

#endif // !__QUADTREE_H__

