#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include "Component.h"
#include <vector>

class Mesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* go);
	~ComponentMesh();

	componentType type;
	
	bool Update();
	bool AddMesh(std::vector<Mesh> _mesh);
	bool DeleteMesh();
	void OnEditor();
private:
	std::vector<Mesh> mesh;
};

#endif // !__COMPONENTMESH_H__