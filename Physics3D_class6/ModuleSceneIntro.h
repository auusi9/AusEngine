#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#define BOUNCER_TIME 200

struct PhysBody3D;
class Cube;
class Mesh;

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
	uint my_id;
	uint my_indices;

	uint id_vertices = 0; 
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_indices = 0; 
	uint num_vertices = 0;
	float* vertices = nullptr;
	std::vector<Mesh> mesh;

	uint texture;
};
