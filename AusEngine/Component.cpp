#include "Component.h"
#include "GameObject.h"

Component::Component()
{
}

Component::Component(componentType _type, GameObject* go)
{
	type = _type;
	gameObject = go;
}

Component::~Component()
{

}

bool Component::Init()
{

	return true;
}

//Enable disable component
void Component::Active()
{
	active = !active;
}

bool Component::Update()
{

	return true;
}

void Component::OnEditor()
{

}