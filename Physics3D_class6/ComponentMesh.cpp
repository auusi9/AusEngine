#include "ComponentMesh.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "Imgui\imgui.h"
#include "ModuleLoadMeshes.h"
using namespace std;

ComponentMesh::ComponentMesh(GameObject* go) : Component(Meshes,go)
{
	Mesh _mesh;
	mesh.push_back(_mesh);
}


ComponentMesh::~ComponentMesh()
{
	mesh.clear();
}

//Renders the current Mesh
bool ComponentMesh::Update()
{
	App->renderer3D->RenderMesh(mesh);
	return true;
}

void ComponentMesh::OnEditor()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		int num_vertices = 0;
		int num_indices = 0;
		for (vector<Mesh>::iterator item = mesh.begin(); item != mesh.end(); ++item)
		{
			num_vertices += (*item).num_vertices;
			num_indices += (*item).num_indices;
		}
		int num_triangles = num_indices/3;

		
		ImGui::Text("Triangles: %d", num_triangles);
		ImGui::Text("Vertices: %d", num_triangles);
		ImGui::Text("Indices: %d", num_indices);
	}
}
//If there is no mesh adds a mesh if there is a mesh changes the current Mesh
bool ComponentMesh::AddMesh(vector<Mesh> _mesh)
{
	mesh = _mesh;
	return true;
}

//Deletes the current Mesh
bool ComponentMesh::DeleteMesh()
{
	mesh.clear();
	return true;
}