#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include "Component.h"

#include "ModuleLoadMeshes.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* go);
	~ComponentMesh();
	
	bool Update();
	bool AddMesh(MeshT _mesh);
	bool DeleteMesh();
	void OnEditor();
	void OnDraw();
	MeshT Cmesh;
};

#endif // !__COMPONENTMESH_H__