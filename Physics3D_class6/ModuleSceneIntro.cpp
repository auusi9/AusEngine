#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleGameObjectManager.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentMesh.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{

	bool ret = true;
	GameObject* go = App->go->AddGameObject(nullptr);
	Component* goT = go->AddComponent(Transform);
	Component* goM = go->AddComponent(Meshes);
	ComponentMesh* goMe = (ComponentMesh*)go->GetComponent(Meshes);
	go->name = "AAA";
	mesh = App->MeshD->Load("Assets/FBX/Town/Street environment_V01.fbx");
	goMe->AddMesh(mesh);
	GameObject* go2 = App->go->AddGameObject(go);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
update_status ModuleSceneIntro::PreUpdate(float dt)
{	
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	Plane(0, 1, 0, 0).Render();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
		return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}
