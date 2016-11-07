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
	GetWorldTransform();
	UpdateChildTransform();
	UpdateBoundingBox();
}

void ComponentTransform::SetRotation(math::float3 _rotationAngles)
{
	angles = _rotationAngles;
	anglesRad = DegToRad(_rotationAngles);
	rotation = rotation.FromEulerXYZ(anglesRad.x, anglesRad.y, anglesRad.z);
	local_transform = local_transform.FromTRS(position, rotation, scale);
	GetWorldTransform();
	UpdateChildTransform();
	UpdateBoundingBox();
}
void ComponentTransform::SetRotationQuat(math::Quat _rotation)
{
	angles = RadToDeg(_rotation.ToEulerXYZ());
	rotation = _rotation;
	local_transform = local_transform.FromTRS(position, rotation, scale);
	GetWorldTransform();
	UpdateChildTransform();
	UpdateBoundingBox();
}
void ComponentTransform::SetScale(math::float3 _scale)
{
	scale = _scale;
	local_transform = local_transform.FromTRS(position, rotation, scale);
	GetWorldTransform();
	UpdateChildTransform();
	UpdateBoundingBox();
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

math::float4x4 ComponentTransform::GetWorldTransformnoCalculate() const
{
	return world_transform;
}

math::float4x4 ComponentTransform::GetWorldTransform() 
{
	 math::float4x4 tmptransform = local_transform;

	if (gameObject->root != nullptr)
	{
		ComponentTransform* parentTransform = (ComponentTransform*)gameObject->root->transform;
		if (parentTransform != nullptr)
		{
			tmptransform =  parentTransform->GetWorldTransform() * tmptransform;
		}
	}
	
	world_transform = tmptransform;
	return tmptransform;
}

void ComponentTransform::UpdateChildTransform() const
{
	for (std::vector<GameObject*>::iterator item = gameObject->goChilds.begin(); item != gameObject->goChilds.end(); ++item)
	{
		ComponentTransform* childTransform = (ComponentTransform*)(*item)->transform;
		if (childTransform != nullptr)
		{
			math::float4x4 tmptransform = childTransform->GetWorldTransform();
			childTransform->UpdateChildTransform();
			childTransform->UpdateBoundingBox();
		}
	}
}

math::float4x4 ComponentTransform::GetLocalTransform() const
{
	return local_transform;
}

void ComponentTransform::GenerateBoundingBox(unsigned int* vertices,unsigned int numVertices)
{
	gBox.SetNegativeInfinity();
	gBox.Enclose((float3*)vertices, numVertices);

	GetWorldTransform();
	tmpObb = gBox.Transform(world_transform);
	TBox = tmpObb.MinimalEnclosingAABB();
}

void ComponentTransform::UpdateBoundingBox()
{
	tmpObb = gBox.Transform(world_transform);
	TBox = tmpObb.MinimalEnclosingAABB();
}

math::AABB ComponentTransform::GetAABB() const
{
	return TBox;
}

math::OBB ComponentTransform::GetOBB() const
{
	return tmpObb;
}