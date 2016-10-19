#include "ComponentTransform.h"
#include "GameObject.h"
#include "Imgui\imgui.h"
#include "Math.h"

ComponentTransform::ComponentTransform(GameObject* go) : Component(Transform,go)
{
	position = { 0,0,0 };
	angles = { 0,0,0 };
	scale = { 1,1,1 };
	local_transform = local_transform.FromTRS(position, rotation, scale);
}

//By the Moment this constructors are usless
ComponentTransform::ComponentTransform(math::float3 _position, math::float3 _rotationAngles, math::float3 _scale, GameObject* go) : Component(Transform,go)
{
	position = _position;
	angles = DegToRad(_rotationAngles);
	scale = _scale;
	SetRotation(angles);
	local_transform = local_transform.FromTRS(position, rotation, scale);
}

ComponentTransform::ComponentTransform(math::float3 _position, math::float3 _rotationAngles, GameObject* go) : Component(Transform,go)
{
	position = _position;
	angles = DegToRad(_rotationAngles);
	scale = {1,1,1};
	SetRotation(angles);
	local_transform = local_transform.FromTRS(position, rotation, scale);
}

ComponentTransform::ComponentTransform(math::float3 _position, GameObject* go) : Component(Transform,go)
{
	position = _position;
	angles = { 0,0,0 };
	scale = { 1,1,1 };
	local_transform = local_transform.FromTRS(position, rotation, scale);
}

ComponentTransform::~ComponentTransform()
{
}


bool ComponentTransform::Update()
{
	return true;
}

//Shows Position, Euler angles in degrees and scale, and allows the user to modify them
void ComponentTransform::OnEditor()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		if (ImGui::DragFloat3("##pos", position.ptr()))
		{
			SetPosition(position);
		}

		if (ImGui::DragFloat3("##ang", angles.ptr()))
		{
			SetRotation(angles);
		}

		if (ImGui::DragFloat3("##sca", scale.ptr()))
		{
			SetScale(scale);
		}
	}
}

void ComponentTransform::SetPosition(math::float3 _position)
{
	position = _position;
	local_transform = local_transform.FromTRS(position, rotation, scale);
	world_transform = GetWorldTransform();
	tmpObb = gameObject->gBox.Transform(world_transform);
	gameObject->gBox.Enclose(tmpObb);
}

void ComponentTransform::SetRotation(math::float3 _rotationAngles)
{
	angles = _rotationAngles;
	anglesRad = DegToRad(_rotationAngles);
	rotation = rotation.FromEulerXYZ(anglesRad.z, anglesRad.y, anglesRad.x);
	local_transform = local_transform.FromTRS(position, rotation, scale);
	world_transform = GetWorldTransform();
	tmpObb = gameObject->gBox.Transform(world_transform);
	gameObject->gBox.Enclose(tmpObb);
}
void ComponentTransform::SetRotationQuat(math::Quat _rotation)
{
	angles = _rotation.ToEulerXYZ();
	rotation = _rotation;
	local_transform = local_transform.FromTRS(position, rotation, scale);
	world_transform = GetWorldTransform();
	tmpObb = gameObject->gBox.Transform(world_transform);
	gameObject->gBox.Enclose(tmpObb);
}
void ComponentTransform::SetScale(math::float3 _scale)
{
	scale = _scale;
	local_transform = local_transform.FromTRS(position, rotation, scale);
	world_transform = GetWorldTransform();
	tmpObb = gameObject->gBox.Transform(world_transform);
	gameObject->gBox.Enclose(tmpObb);
}

math::float3 ComponentTransform::GetPosition() const
{
	return position;
}

math::float3 ComponentTransform::GetCurrentAngles() const
{
	return angles;
}

math::float3 ComponentTransform::GetScale() const
{
	return scale;
}

math::float3 ComponentTransform::GetWorldPosition() const 
{
	math::float3 tmpposition = position;

	if (gameObject->root != nullptr)
	{
		ComponentTransform* parentTransform = (ComponentTransform*)gameObject->root->GetComponent(Transform);
		if (parentTransform != nullptr)
			tmpposition += parentTransform->GetWorldPosition();
	}

	return tmpposition;
}

math::float4x4 ComponentTransform::GetWorldTransform() const
{
	math::float4x4 tmptransform = local_transform;

	if (gameObject->root != nullptr)
	{
		ComponentTransform* parentTransform = (ComponentTransform*)gameObject->root->GetComponent(Transform);
		if(parentTransform != nullptr)
			tmptransform =  parentTransform->GetWorldTransform() * tmptransform;
	}

	return tmptransform;
}

math::float4x4 ComponentTransform::GetLocalTransform() const
{
	return local_transform;
}