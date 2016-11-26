#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ComponentCamera.h"
#include "ModuleRenderer3D.h"
#include "ModuleGameObjectManager.h"
#include "GameObject.h"
#include <vector>

using namespace std;

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	dummy = new ComponentCamera(nullptr);
	picking = LineSegment(float3::zero, float3::unitY);
	last_hit = float3::zero;
}

ModuleCamera3D::~ModuleCamera3D()
{
	RELEASE(dummy);
}

// -----------------------------------------------------------------
bool ModuleCamera3D::Init()
{
	App->renderer3D->active_camera = dummy;

	return true;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	App->renderer3D->active_camera = nullptr;
	return true;
}

// -----------------------------------------------------------------
/*void ModuleCamera3D::Save(Config * config) const
{
	config->AddFloat("Mov Speed", mov_speed);
	config->AddFloat("Rot Speed", rot_speed);
	config->AddFloat("Zoom Speed", zoom_speed);
	dummy->OnSave(*config);
}*/

// -----------------------------------------------------------------
/*void ModuleCamera3D::Load(Config * config)
{
	// Beware, this method will be called again when loading a level!
	mov_speed = config->GetFloat("Mov Speed", mov_speed); // global var, not level specific
	rot_speed = config->GetFloat("Rot Speed", rot_speed); // global var, not level specific
	zoom_speed = config->GetFloat("Zoom Speed", zoom_speed); // global var, not level specific
	dummy->OnLoad(config);
}*/

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	Frustum* frustum = &dummy->frustum;
	// Keyboard for WASD movement -------
	if (App->imgui->UsingKeyboard() == false)
		Move(dt);

	// Mouse ----------------------------
	if (App->imgui->UsingMouse() == false)
	{
		// Check motion for lookat / Orbit cameras
		int motion_x, motion_y;
		App->input->GetMouseMotion(motion_x, motion_y);
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && (motion_x != 0 || motion_y != 0))
		{
			float dx = (float)-motion_x * rot_speed * dt;
			float dy = (float)-motion_y * rot_speed * dt;

			if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
				Orbit(dx, dy);
			else
				LookAt(dx, dy);
		}

		// Mouse wheel for zoom
		int wheel = App->input->GetMouseWheel();
		if (wheel != 0)
			Zoom(wheel * zoom_speed * dt);

		// Mouse Picking
		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
		/*	GameObject* pick = Pick();
			if (pick != nullptr)
				App->editor->SetSelected(pick, (App->editor->selected == pick));*/
		}
	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
float3 ModuleCamera3D::GetPosition() const
{
	return dummy->frustum.pos;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3& position)
{
	dummy->Look(position);
}

// -----------------------------------------------------------------
void ModuleCamera3D::CenterOn(const float3& position, float distance)
{
	float3 v = dummy->frustum.front.Neg();
	dummy->frustum.pos = position + (v * distance);
	looking_at = position;
	looking = true;
}

// -----------------------------------------------------------------
ComponentCamera * ModuleCamera3D::GetDummy() const
{
	return dummy;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Move(float dt)
{
	Frustum* frustum = &dummy->frustum;

	float adjusted_speed = mov_speed;

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) adjusted_speed *= 5.0f;
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) adjusted_speed *= 0.5f;

	float3 right(frustum->WorldRight());
	float3 forward(frustum->front);

	float3 movement(float3::zero);

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) movement += forward;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) movement -= forward;
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) movement -= right;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) movement += right;
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) movement += float3::unitY;
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) movement -= float3::unitY;

	if (movement.Equals(float3::zero) == false)
	{
		frustum->Translate(movement * (adjusted_speed * dt));
		looking = false;
	}
}

// -----------------------------------------------------------------
void ModuleCamera3D::Orbit(float dx, float dy)
{
	float3 point = looking_at;

	// fake point should be a ray colliding with something
	if (looking == false)
	{
		LineSegment picking = dummy->frustum.UnProjectLineSegment(0.f, 0.f);
		float distance;
		/*GameObject* hit = App->level->CastRay(picking, distance);

		if (hit != nullptr)
			point = picking.GetPoint(distance);
		else
			point = dummy->frustum.pos + dummy->frustum.front * 50.0f;
			*/
		looking = true;
		looking_at = point;
	}

	float3 focus = dummy->frustum.pos - point;

	Quat qy(dummy->frustum.up, dx);
	Quat qx(dummy->frustum.WorldRight(), dy);

	focus = qx.Transform(focus);
	focus = qy.Transform(focus);

	dummy->frustum.pos = focus + point;

	Look(point);
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(float dx, float dy)
{
	looking = false;

	// x motion make the camera rotate in Y absolute axis (0,1,0) (not local)
	if (dx != 0.f)
	{
		Quat q = Quat::RotateY(dx);
		dummy->frustum.front = q.Mul(dummy->frustum.front).Normalized();
		// would not need this is we were rotating in the local Y, but that is too disorienting
		dummy->frustum.up = q.Mul(dummy->frustum.up).Normalized();
	}

	// y motion makes the camera rotate in X local axis, with tops
	if (dy != 0.f)
	{
		Quat q = Quat::RotateAxisAngle(dummy->frustum.WorldRight(), dy);

		float3 new_up = q.Mul(dummy->frustum.up).Normalized();

		if (new_up.y > 0.0f)
		{
			dummy->frustum.up = new_up;
			dummy->frustum.front = q.Mul(dummy->frustum.front).Normalized();
		}
	}
}

// -----------------------------------------------------------------
void ModuleCamera3D::Zoom(float zoom)
{
	if (looking == true)
	{
		float dist = looking_at.Distance(dummy->frustum.pos);

		// Slower on closer distances
		if (dist < 15.0f)
			zoom *= 0.5f;
		if (dist < 7.5f)
			zoom *= 0.25f;
		if (dist < 1.0f && zoom > 0)
			zoom = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		zoom *= 5.0f;

	float3 p = dummy->frustum.front * zoom;
	dummy->frustum.pos += p;
}

// -----------------------------------------------------------------
GameObject* ModuleCamera3D::Pick(float3* hit_point) const
{
	GameObject* g;
	return g;
}