#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "Component.h"
#include "MathGeoLib\src\Math\float3.h"

class ComponentTransform : Component
{
public:
	ComponentTransform();
	ComponentTransform(float3 _position, float3 _rotation ,float3 _scale);
	ComponentTransform(float3 _position, float3 _rotation);
	ComponentTransform(float3 _position);
	~ComponentTransform();

	componentType type;

	bool Update();
	float3 position;
	float3 rotation;
	float3 scale;
private:
};

#endif // !__COMPONENTTRANSFORM_H__