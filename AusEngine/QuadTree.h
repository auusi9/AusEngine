#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Math.h"
#include <vector>

class GameObject;

class QuadtreeNode
{
public:
	QuadtreeNode();
	~QuadtreeNode();
	bool Create(math::AABB box);
	bool Clear();
	int Insert(GameObject* go);
	bool Remove(GameObject* go);

	template<typename TYPE>
	inline void Intersect(std::vector<GameObject*> &go, const TYPE &primitive);

};





class Quadtree
{
public:
	Quadtree();
	~Quadtree();


private:

};


#endif // !__QUADTREE_H__

