#ifndef  __MODULELOADMESHES_H__
#define __MODULELOADMESHES_H__

#include "Module.h"
#include <cstdint>
#include <vector>
class aiNode;
class aiScene;
class GameObject;

struct MeshT
{
	uint id_vertices;
	uint num_vertices;
	uint* vertices = nullptr;

	uint id_indices;
	uint num_indices;
	uint* indices = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = nullptr;

	uint id_uvs = 0;
	uint num_uvs = 0;
	float* uvs = nullptr;
};

class ModuleLoadMeshes : public Module
{
public:
	ModuleLoadMeshes(Application* app, bool start_enabled = true);
	~ModuleLoadMeshes();

	bool Init();
	bool CleanUp();

	std::vector<MeshT> LoadMesh(const char* path);
	void LoadCurrentNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* path);
	uint LoadTexture(const char* path);
};

#endif // __MODULEMESHES_H__
