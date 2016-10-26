#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "Component.h"
#include "MathGeoLib/src/MathGeoLib.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* go);
	ComponentTransform(math::float3 _position, math::float3 _rotation , math::float3 _scale, GameObject* go);
	ComponentTransform(math::float3 _position, math::float3 _rotation, GameObject* go);
	ComponentTransform(math::float3 _position, GameObject* go);
	~ComponentTransform();
	
	bool Update();
	void OnEditor();

	void SetPosition(math::float3 _position);
	void SetRotation(math::float3 _rotation);
	void SetRotationQuat(math::Quat _rotationAngles);
	void SetScale(math::float3 _scale);

	math::float3 GetPosition() const;
	math::float3 GetCurrentAngles() const;
	math::float3 GetScale() const;

	math::float3 GetWorldPosition() const;

	math::float4x4 GetWorldTransform() const;
	math::float4x4 GetLocalTransform() const;

	void GenerateBoundingBox(unsigned int* vertices, unsigned int numVertices);
	math::AABB GetAABB() const;
private:
	//Made this private because its the local transform and it depends on the parent.
	math::float3 position = math::float3::zero;
	math::Quat rotation = math::Quat::identity;
	math::float3 angles = math::float3::zero;
	math::float3 anglesRad = math::float3::zero;
	math::float3 scale = math::float3::zero;
	math::float4x4 local_transform = math::float4x4::zero;
	math::float4x4 world_transform = math::float4x4::zero;
	math::AABB gBox;
	math::OBB tmpObb;
};

#endif // !__COMPONENTTRANSFORM_H__