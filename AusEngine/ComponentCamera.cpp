#include "ComponentCamera.h"
#include "Imgui\imgui.h"
#include "GameObject.h"


ComponentCamera::ComponentCamera(GameObject* go) : Component(Camera, go)
{
	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 1000.0f;
	frustum.verticalFov = DEGTORAD * 60.0f;
	aspectRatio = 16 / 9;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)* aspectRatio);

}


ComponentCamera::~ComponentCamera()
{

}


bool ComponentCamera::Init()
{

	return true;
}

bool ComponentCamera::Update()
{

	return true;
}


void ComponentCamera::OnEditor()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		
	}
}

void ComponentCamera::SetFov(float fov)
{
	frustum.verticalFov = DEGTORAD * 60.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)* aspectRatio);
}

void ComponentCamera::SetAspectRatio(float w, float h)
{
	aspectRatio = w / h;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)* aspectRatio);
}

