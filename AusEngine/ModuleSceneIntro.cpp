#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleGameObjectManager.h"
#include "GameObject.h"
#include "ModuleLoadMeshes.h"
#include "Component.h"
ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	bool ret = true;

	sceneObjects = App->MeshD->Load("Assets/FBX/Street environment_V01.fbx");
	(*sceneObjects.begin())->AddComponent(Transform);
	App->go->toTest = (ComponentCamera*)(*sceneObjects.begin())->AddComponent(Camera);
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	sceneObjects.clear();
	return true;
}
update_status ModuleSceneIntro::PreUpdate(float dt)
{	
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
		return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}
