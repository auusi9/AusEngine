#ifndef  __MODULELOADTEXTURES_H__
#define __MODULELOADTEXTURES_H__

#include "Module.h"

class ModuleLoadTextures : public Module
{
public:
	ModuleLoadTextures(Application* app, bool start_enabled = true);
	~ModuleLoadTextures();

	bool Init();
	bool CleanUp();

};

#endif // __MODULELOADTEXTURES_H__