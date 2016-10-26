#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "Math.h"
using namespace std;

GameObject::GameObject()
{
	root = nullptr;
	name.resize(20);
	name = "GameObject";
}

GameObject::GameObject(GameObject* parent)
{
	root = parent;
	name.resize(20);
	name = "GameObject";
}

GameObject::~GameObject()
{
	root = nullptr;
}
//Call all the cleanUps of the childs and then release all the childs and components of the gameobject
bool GameObject::CleanUp()
{
	for (vector<GameObject*>::iterator item = goChilds.begin(); item != goChilds.end(); ++item)
	{
		(*item)->CleanUp();
		RELEASE(*item);
	}
	goChilds.clear();

	for (vector<Component*>::iterator item = Components.begin(); item != Components.end(); ++item)
	{
		RELEASE(*item);	
	}
	Components.clear();

	return true;
}
bool GameObject::Start()
{
	return true;
}

bool GameObject::Update()
{
	bool ret = true;

	//Call each Component Update
	for (vector<Component*>::iterator item = Components.begin(); item != Components.end(); ++item)
	{
		(*item)->Update();
	}

	//Call each Child Update
	for (vector<GameObject*>::iterator item = goChilds.begin(); item != goChilds.end(); ++item)
	{
		(*item)->Update();
	}

	return ret;
}

Component* GameObject::AddComponent(componentType _type)
{
	Component* component = NULL;
	//Check there are no duplicate Components
	component = GetComponent(_type);
	if (component != nullptr)
		return component;

	switch (_type)
	{
		case Transform: component = new ComponentTransform(this); 
			break;

		case Meshes: component = new ComponentMesh(this);
			break;

		case Material: component = new ComponentMaterial(this);
			break;

		default: component = new ComponentTransform(this); 
			break;
	}

	Components.push_back(component);
	return component;
}

//Returns the first component of type
Component* GameObject::GetComponent(componentType _type)
{

	Component* component = NULL;

	for (vector<Component*>::iterator item = Components.begin(); item != Components.end(); ++item)
	{
		if ((*item)->type == _type)
		{
			component = (*item);
			break;
		}
	}

	return component;
}

bool GameObject::RemoveChild(GameObject* child)
{
	bool ret = false;

	for (vector<GameObject*>::iterator item = goChilds.begin(); item != goChilds.end(); ++item)
	{
		if ((*item) == child)
		{
			goChilds.erase(item);
			child->CleanUp();
			RELEASE(child);
			ret = true;
		}
	}

	return ret;
}

