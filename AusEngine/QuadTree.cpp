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
	bool ret = false;

	if (box.Contains(go->transform->GetWorldPosition()))
	{
		if (childs.size() > 0)
		{
			for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
			{
				if ((*item)->Insert(go))
				{
					return true;
				}
					
			}
		}
		else
		{
			if (objects.size() > 4)
			{
				Divide();
				for (std::list<GameObject*>::iterator item = objects.begin(); item != objects.end(); ++item)
				{
					Insert(*item);
				}
				objects.clear();

				for (std::vector<QuadtreeNode*>::iterator item = childs.begin(); item != childs.end(); ++item)
				{
					if ((*item)->Insert(go))
						break;
				}
				return true;
			}
			else
			{
				objects.push_back(go);
				ret = true;
			}

		}
	}

	return ret;
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
	math::AABB new_box;
	for (int i = 0; i < 4; i++)
	{
		new_box = box;

		if (i == 0)
		{
			new_box.minPoint.z /= 2;
			new_box.maxPoint.x /= 2;
		}

		if (i == 1)
		{
			new_box.minPoint.x /= 2;
			new_box.minPoint.z /= 2;
		}

		if (i == 2)
		{
			new_box.maxPoint.x /= 2;
			new_box.maxPoint.z /= 2;
		}

		if (i == 3)
		{
			new_box.minPoint.x /= 2;
			new_box.maxPoint.z /= 2;
		}

		QuadtreeNode* node = new QuadtreeNode(new_box);
		node->parent = this;
		childs.push_back(node);
	}
}










