#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleImGui : public Module
{
public:
	ModuleImGui(Application* app, bool start_enabled = true);
	~ModuleImGui();

	bool Init();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();

};
