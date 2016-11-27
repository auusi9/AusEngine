#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Globals.h"
#include <vector>
class Component;
enum componentType;
class AABB;
class ComponentTransform;
class ComponentMesh;
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
	bool GetStatic();
	bool GetActive();

	Component* AddComponent(componentType _type);
	Component* GetComponent(componentType _type);
	std::vector<Component*> Components;
	
	ComponentTransform* transform = nullptr;
	ComponentMesh* mesh = nullptr;
	
private:
	bool isStatic = false;
	bool Active = true;
};

#endif // !__GAMEOBJECT_H__
