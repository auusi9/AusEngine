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
	uint idVertices = 0;
	uint numVertices = 0;
	uint* vertices = nullptr;

	uint idIndices = 0;
	uint numIndices = 0;
	uint* indices = nullptr;

	uint idNormals = 0;
	uint numNormals = 0;
	float* normals = nullptr;

	uint idUvs = 0;
	uint numUvs = 0;
	float* uvs = nullptr;

	math::AABB gBox;
};

class ModuleLoadMeshes : public Module
{
public:
	ModuleLoadMeshes(Application* app, bool start_enabled = true);
	~ModuleLoadMeshes();

	bool Init();
	bool CleanUp();

	std::vector<GameObject*> Load(const char* path);
	GameObject* LoadMesh(const aiScene* scene, aiNode* node, const char* path, GameObject* parent);
	uint LoadTexture(const char* path);
};

#endif // __MODULEMESHES_H__
