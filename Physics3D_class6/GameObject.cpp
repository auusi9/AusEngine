#include "GameObject.h"
#include "Component.h"
#include "Globals.h"

using namespace std;

GameObject::GameObject(GameObject* parent)
{

}

GameObject::~GameObject()
{

}
//Call all the cleanUps of the childs and then release all the childs and components of the gameobject
bool GameObject::CleanUp()
{
	for (vector<GameObject*>::iterator item = goChilds.begin(); item != goChilds.end(); ++item)
	{
		(*item)->CleanUp();
		goChilds.pop_back();
		RELEASE(*item);
	}

	for (vector<Component*>::iterator item = Components.end(); item != Components.begin(); --item)
	{
		Components.pop_back();
		RELEASE(*item);
	}

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
	Component* component = new Component(_type);
	Components.push_back(component);
	return component;
}