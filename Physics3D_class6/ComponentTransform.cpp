#include "ComponentTransform.h"
#include "GameObject.h"
#include "Imgui\imgui.h"

ComponentTransform::ComponentTransform(GameObject* go) : Component(Transform,go)
{
	position = { 0,0,0 };
	angles = { 0,0,0 };
	scale = { 1,1,1 };
}

ComponentTransform::ComponentTransform(math::float3 _position, math::float3 _rotationAngles, math::float3 _scale, GameObject* go) : Component(Transform,go)
{
	position = _position;
	angles = _rotationAngles;
	scale = _scale;
}

ComponentTransform::ComponentTransform(math::float3 _position, math::float3 _rotationAngles, GameObject* go) : Component(Transform,go)
{
	position = _position;
	angles = _rotationAngles;
	scale = {1,1,1};
}

ComponentTransform::ComponentTransform(math::float3 _position, GameObject* go) : Component(Transform,go)
{
	position = _position;
	angles = { 0,0,0 };
	scale = { 1,1,1 };
}

ComponentTransform::~ComponentTransform()
{

}


bool ComponentTransform::Update()
{

	return true;
}

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
			SetScale(angles);
		}
	}


}

void ComponentTransform::SetPosition(math::float3 _position)
{
	position = _position;
}

void ComponentTransform::SetRotation(math::float3 _rotationAngles)
{
	angles = _rotationAngles;
}

void ComponentTransform::SetScale(math::float3 _scale)
{
	scale = _scale;
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
		tmpposition += parentTransform->GetWorldPosition();
	}

	return tmpposition;
}