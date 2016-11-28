#include "Globals.h"
#include "ComponentCamera.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleGameObjectManager.h"
#include "ComponentTransform.h"
#include "Imgui\imgui.h"
// ---------------------------------------------------------
ComponentCamera::ComponentCamera(GameObject* go) : Component(Camera,go)
{
	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 200.0f;
	frustum.verticalFov = DEGTORAD * 60.0f;
	SetAspectRatio(1.3f);

	background = Black;
	projection_changed = true;
}

// ---------------------------------------------------------
ComponentCamera::~ComponentCamera()
{}

// ---------------------------------------------------------
bool ComponentCamera::Init()
{
	if (looking_at_uid != 0)
	{
		//looking_at = App->go->Find(looking_at_uid);
	}
		
		
	return true;
}

// ---------------------------------------------------------
bool ComponentCamera::Update()
{
	if (looking_at != nullptr)
		Look(looking_at->transform->GetWorldPosition());

	App->renderer3D->RenderDebugFrustrum(frustum);
	return true;
}

// ---------------------------------------------------------
/*void ComponentCamera::OnSave(Config& config) const
{
	config.AddUInt("Looking At", (looking_at) ? looking_at->GetUID() : 0);
	config.AddArrayFloat("Background", (float*)&background, 4);
	config.AddArrayFloat("Frustum", (float*)&frustum.pos.x, 13);
}*/

// ---------------------------------------------------------
/*void ComponentCamera::OnLoad(Config * config)
{
	uint looking_at_uid = config->GetUInt("Looking At", 0);

	background.r = config->GetFloat("Background", 0.f, 0);
	background.g = config->GetFloat("Background", 0.f, 1);
	background.b = config->GetFloat("Background", 0.f, 2);
	background.a = config->GetFloat("Background", 1.f, 3);

	frustum.pos.x = config->GetFloat("Frustum", 0.f, 0);
	frustum.pos.y = config->GetFloat("Frustum", 0.f, 1);
	frustum.pos.z = config->GetFloat("Frustum", 0.f, 2);

	frustum.front.x = config->GetFloat("Frustum", 0.f, 3);
	frustum.front.y = config->GetFloat("Frustum", 0.f, 4);
	frustum.front.z = config->GetFloat("Frustum", 1.f, 5);

	frustum.up.x = config->GetFloat("Frustum", 0.f, 6);
	frustum.up.y = config->GetFloat("Frustum", 1.f, 7);
	frustum.up.z = config->GetFloat("Frustum", 0.f, 8);

	frustum.nearPlaneDistance = config->GetFloat("Frustum", 0.1f, 9);
	frustum.farPlaneDistance = config->GetFloat("Frustum", 1000.f, 10);

	frustum.horizontalFov = config->GetFloat("Frustum", 1.f, 11);
	frustum.verticalFov = config->GetFloat("Frustum", 1.f, 12);

	projection_changed = true;
}*/

// -----------------------------------------------------------------
void ComponentCamera::OnUpdateTransform()
{
	float4x4 trans = gameObject->transform->GetWorldTransformnoCalculate();

	frustum.pos = trans.TranslatePart();
	frustum.front = trans.WorldZ();
	frustum.up = trans.WorldY();
}

void ComponentCamera::OnEditor()
{
	float new_fov = 0.0f;
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::TreeNode("FOV"))
		{
			new_fov = GetFOV();
			if (ImGui::SliderFloat("H. Fov", &new_fov, 0.1f, 179.5f, "%.1f"))
			{
					SetFOV(new_fov);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("AspectRatio"))
		{
			new_fov = GetAspectRatio();
			if (ImGui::SliderFloat("AspectRatio", &new_fov, 0, 20, "%.1f"))
			{
				SetAspectRatio(new_fov);
			}

			ImGui::TreePop();
		}
		float asp_rat_vec[2];
		if (ImGui::TreeNode("Planes"))
		{
			asp_rat_vec[0] = frustum.nearPlaneDistance;
			asp_rat_vec[1] = frustum.farPlaneDistance;

			if (ImGui::SliderFloat("Near Plane", &frustum.nearPlaneDistance, 1, frustum.farPlaneDistance, "%.0f"))
			{
			}

			if (ImGui::SliderFloat("Far Plane", &frustum.farPlaneDistance, frustum.nearPlaneDistance, 200, "%.0f")) 
			{
			}
			ImGui::TreePop();
		}
	}
}

// ---------------------------------------------------------
float ComponentCamera::GetNearPlaneDist() const
{
	return frustum.nearPlaneDistance;
}

// ---------------------------------------------------------
float ComponentCamera::GetFarPlaneDist() const
{
	return frustum.farPlaneDistance;
}

// ---------------------------------------------------------
float ComponentCamera::GetFOV() const
{
	return frustum.verticalFov * RADTODEG;
}

// ---------------------------------------------------------
float ComponentCamera::GetAspectRatio() const
{
	return frustum.AspectRatio();
}

// ---------------------------------------------------------
void ComponentCamera::SetNearPlaneDist(float dist)
{
	if (dist > 0.0f && dist < frustum.farPlaneDistance)
	{
		frustum.nearPlaneDistance = dist;
		projection_changed = true;
	}
}

// ---------------------------------------------------------
void ComponentCamera::SetFarPlaneDist(float dist)
{
	if (dist > 0.0f && dist > frustum.nearPlaneDistance)
	{
		frustum.farPlaneDistance = dist;
		projection_changed = true;
	}
}

// ---------------------------------------------------------
void ComponentCamera::SetFOV(float fov)
{
	float aspect_ratio = frustum.AspectRatio();

	frustum.verticalFov = DEGTORAD * fov;
	SetAspectRatio(aspect_ratio);
}

// ---------------------------------------------------------
void ComponentCamera::SetHFOV(float fov)
{
	float aspect_ratio = frustum.AspectRatio();

	frustum.horizontalFov = DEGTORAD * fov;
	SetAspectRatio(aspect_ratio);
}

// ---------------------------------------------------------
void ComponentCamera::SetAspectRatio(float aspect_ratio)
{
	// More about FOV: http://twgljs.org/examples/fov-checker.html
	// fieldOfViewX = 2 * atan(tan(fieldOfViewY * 0.5) * aspect)
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspect_ratio);
	projection_changed = true;
}

// -----------------------------------------------------------------
void ComponentCamera::Look(const float3& position)
{
	float3 dir = position - frustum.pos;

	float3x3 m = float3x3::LookAt(frustum.front, dir.Normalized(), frustum.up, float3::unitY);

	frustum.front = m.MulDir(frustum.front).Normalized();
	frustum.up = m.MulDir(frustum.up).Normalized();
}

// -----------------------------------------------------------------
float* ComponentCamera::GetOpenGLViewMatrix()
{
	static float4x4 m;

	m = frustum.ViewMatrix();
	m.Transpose();

	return (float*)m.v;
}

// -----------------------------------------------------------------
float* ComponentCamera::GetOpenGLProjectionMatrix()
{
	static float4x4 m;

	m = frustum.ProjectionMatrix();
	m.Transpose();

	return (float*)m.v;
}

// ----------------------------------------------------------------
bool ComponentCamera::ContainsAaBox(const math::AABB& refBox) const
{

	float3 vCorner[8];

	refBox.GetCornerPoints(vCorner);

	math::Plane m_plane[6];
	frustum.GetPlanes(m_plane);

	int out;
	for (int i = 0; i < 6; ++i)
	{
		out = 0;
		for (int k = 0; k < 8; ++k)
			out += m_plane[i].IsOnPositiveSide(vCorner[k]);

		if (out == 8)
			return false;
	}


	return true;
}