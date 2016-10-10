#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <vector>
class Component;
enum componentType;

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	char* name = "GameObject";

	GameObject* gameobject = this;
	GameObject* root;
	std::vector<GameObject*> goChilds;

	bool Start();
	Component* AddComponent(componentType _type);
	bool Update();
	bool CleanUp();
	std::vector<Component*> Components;

private:

};

#endif // !__GAMEOBJECT_H__
