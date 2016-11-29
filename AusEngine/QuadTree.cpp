#include "Quadtree.h"
#include "GameObject.h"
#include "ComponentTransform.h"



Quadtree::Quadtree(math::AABB box)
{
	root = new QuadtreeNode(box);
}


Quadtree::~Quadtree()
{
	root->Clear();

}


QuadtreeNode::QuadtreeNode(math::AABB &_box) : box(_box)
{
	parent = nullptr;
}

QuadtreeNode::~QuadtreeNode()
{
	parent = nullptr;
}

bool QuadtreeNode::Create(math::AABB box)
{

	//this->box.SetFrom(box);

	return true;
}


bool QuadtreeNode::Clear()
{

	for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
	{
		(*item)->Clear();
		RELEASE(*item);
	}

	childs.clear();

	return true;
}

bool QuadtreeNode::Insert(GameObject* go)
{
	
	if (!box.Contains(go->transform->GetWorldPosition()))
	{
		return false;
	}

	if (objects.size() < 4)
	{
		objects.push_back(go);
		return true;
	}
	
	if (childs.empty())
			Divide();
		
	for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
	{
			if ((*item)->Insert(go))
				return true;
	}

	
		/*if (box.Contains(go->transform->GetWorldPosition()))
		{
			if (childs.size() > 0)
			{
				for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
				{
					if ((*item)->Insert(go))
					{
					}
					
				}
			}
			else
			{
				if (objects.size() < 4)
				{
					objects.push_back(go);
					ret = true;
				}
				else
				{
					Divide();
					
					for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
					{
						if ((*item)->Insert(go))
							break;
					}
				}

			}
	}*/

	
}

bool QuadtreeNode::Remove(GameObject* go)
{
	bool ret = false;
	for (std::list<GameObject*>::iterator item = objects.begin(); item != objects.end(); ++item)
	{
		if ((*item) == go)
		{
			objects.erase(item);//Maybe the node has no objects and childs and can be deleted but for now,I'm going to leave it like this.
			return true;
		}
	}

	if (ret == false)
	{
		for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
		{
			if ((*item)->Remove(go))
			{
				return true;
			}
		}
	}

	return ret;
}

void QuadtreeNode::Divide()
{
	// We need to subdivide this node ...
	float3 size(box.Size());
	float3 new_size(size.x*0.5f, size.y, size.z*0.5f); // Octree would subdivide y too

	float3 center(box.CenterPoint());
	float3 new_center(center);
	math::AABB new_box;

	// NorthEast
	new_center.x = center.x + size.x * 0.25f;
	new_center.z = center.z + size.z * 0.25f;
	new_box.SetFromCenterAndSize(new_center, new_size);
	QuadtreeNode* child = new QuadtreeNode(new_box);
	child->parent = this;
	childs.push_back(child);

	// SouthEast
	new_center.x = center.x + size.x * 0.25f;
	new_center.z = center.z - size.z * 0.25f;
	new_box.SetFromCenterAndSize(new_center, new_size);
	QuadtreeNode* child1 = new QuadtreeNode(new_box);
	child1->parent = this;
	childs.push_back(child1);
	// SouthWest
	new_center.x = center.x - size.x * 0.25f;
	new_center.z = center.z - size.z * 0.25f;
	new_box.SetFromCenterAndSize(new_center, new_size);
	QuadtreeNode* child2 = new QuadtreeNode(new_box);
	child2->parent = this;
	childs.push_back(child2);
	// NorthWest
	new_center.x = center.x - size.x * 0.25f;
	new_center.z = center.z + size.z * 0.25f;
	new_box.SetFromCenterAndSize(new_center, new_size);
	QuadtreeNode* child3 = new QuadtreeNode(new_box);
	child3->parent = this;
	childs.push_back(child3);
}










