#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#define BOUNCER_TIME 200

struct PhysBody3D;
class Cube;
class GameObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();
	update_status PostUpdate(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	std::vector<GameObject*> sceneObjects;
};
