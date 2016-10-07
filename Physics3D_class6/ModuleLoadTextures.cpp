#include "ModuleLoadTextures.h"

ModuleLoadTextures::ModuleLoadTextures(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleLoadTextures::~ModuleLoadTextures()
{}


bool ModuleLoadTextures::Init()
{
	return true;
}

bool ModuleLoadTextures::CleanUp()
{
	return true;
}