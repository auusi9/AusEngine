#include "Application.h"
#include "ModuleRenderer3D.h"
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
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = DEGTORAD * 60.0f;
	aspectRatio = 16 / 9;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)* aspectRatio);
	color = { 0.0f, 0.0f, 0.0f };
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
	App->renderer3D->RenderDebugFrustrum(frustum);
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

bool ComponentCamera::ContainsAaBox(const math::AABB& refBox) const
{

	float3 vCorner[8];

	refBox.GetCornerPoints(vCorner); 		

	math::Plane m_plane[6];
	frustum.GetPlanes(m_plane);

	for (int p = 0; p < 6; ++p) 
	{
		int isOut = 8;

		for (int i = 0; i < 8; ++i) 
		{

			// test this point against the planes
			
			if (m_plane[p].IsOnPositiveSide(vCorner[i])) 
			{
				--isOut;
			}
		}
		if (isOut == 8)
		{
			return false;
		}
	}

	return true;
}