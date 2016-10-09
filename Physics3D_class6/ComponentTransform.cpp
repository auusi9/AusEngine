#include "ComponentTransform.h"


ComponentTransform::ComponentTransform()
{
	position = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
}

ComponentTransform::ComponentTransform(float3 _position, float3 _rotation, float3 _scale)
{
	position = _position;
	rotation = _rotation;
	scale = _scale;
}

ComponentTransform::ComponentTransform(float3 _position, float3 _rotation)
{
	position = _position;
	rotation = _rotation;
	scale = {1,1,1};
}

ComponentTransform::ComponentTransform(float3 _position)
{
	position = _position;
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
}

ComponentTransform::~ComponentTransform()
{

}


bool ComponentTransform::Update()
{

	return true;
}