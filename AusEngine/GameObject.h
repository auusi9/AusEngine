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

private:

};

#endif // !__GAMEOBJECT_H__
