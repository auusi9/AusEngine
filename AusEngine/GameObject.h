#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "Globals.h"
#include <vector>
class Component;
enum componentType;

class OBB;

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	std::string name;

	GameObject* gameobject = this;
	GameObject* root;
	std::vector<GameObject*> goChilds;

	bool Start();
	bool Update();
	bool CleanUp();

	bool RemoveChild(GameObject* child);

	Component* AddComponent(componentType _type);
	Component* GetComponent(componentType _type);
	std::vector<Component*> Components;
	
	math::AABB gBox = math::AABB::AABB();
	void GenerateBoundingBox(uint* vertices, uint numVertices);
	
private:

};

#endif // !__GAMEOBJECT_H__
