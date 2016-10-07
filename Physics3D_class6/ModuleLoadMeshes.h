#ifndef  __MODULELOADMESHES_H__
#define __MODULELOADMESHES_H__

#include "Module.h"
#include <cstdint>

struct Mesh
{
	//Vertices
	uint id_vertices = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;

	//Indices
	uint id_indices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;
};

class ModuleLoadMeshes : public Module
{
public:
	ModuleLoadMeshes(Application* app, bool start_enabled = true);
	~ModuleLoadMeshes();

	bool Init();
	bool CleanUp();

	std::vector<Mesh> Load(const char* path);
};

#endif // __MODULEMESHES_H__
