#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include "Component.h"

#include "ModuleLoadMeshes.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* go);
	~ComponentMesh();

	componentType type;
	
	bool Update();
	bool AddMesh(MeshT _mesh);
	bool DeleteMesh();
	void OnEditor();
	MeshT Cmesh;
private:
	
};

#endif // !__COMPONENTMESH_H__