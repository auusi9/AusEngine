#include "Component.h"

Component::Component()
{

}

Component::Component(componentType _type)
{

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