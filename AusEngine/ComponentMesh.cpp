#include "ComponentMesh.h"
#include "Application.h"


#include "ModuleRenderer3D.h"
#include "Imgui\imgui.h"

#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "GameObject.h"
#include "MathGeoLib\src\MathGeoLib.h"
using namespace std;

//Initialize the mesh for security
ComponentMesh::ComponentMesh(GameObject* go) : Component(Meshes,go)
{
	MeshT _mesh;
	Cmesh = _mesh;
	
}


ComponentMesh::~ComponentMesh()
{
}

//Renders the current Mesh
bool ComponentMesh::Update()
{
	ComponentTransform* transform = gameObject->transform;
	ComponentMaterial* material = (ComponentMaterial*)gameObject->GetComponent(Material);

	if (transform == nullptr && material == nullptr)
		App->renderer3D->RenderMesh(Cmesh, math::float4x4::identity, 0);
	else if( material == nullptr)
		App->renderer3D->RenderMesh(Cmesh, transform->GetWorldTransform(), 0);
	else if (transform == nullptr)
		App->renderer3D->RenderMesh(Cmesh, math::float4x4::identity, material->textureId);
	else
		App->renderer3D->RenderMesh(Cmesh, transform->GetWorldTransform(), material->textureId);

	App->renderer3D->RenderDebugAABB(transform->GetOBB(), transform->GetWorldTransform());

	return true;
}

void ComponentMesh::OnEditor()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		int numTriangles = Cmesh.numIndices/3;

		ImGui::Text("Triangles: %d", numTriangles);
		ImGui::Text("Vertices: %d", Cmesh.numVertices);
		ImGui::Text("Indices: %d", Cmesh.numIndices);
	}
}
//If there is no mesh adds a mesh if there is a mesh changes the current Mesh
bool ComponentMesh::AddMesh(MeshT _mesh)
{
	Cmesh = _mesh;
	ComponentTransform* transform = (ComponentTransform*)gameObject->GetComponent(Transform);
	transform->GenerateBoundingBox(Cmesh.vertices, Cmesh.numVertices);
	return true;
}

//Deletes the current Mesh
bool ComponentMesh::DeleteMesh()
{
	MeshT _mesh;
	Cmesh = _mesh;
	return true;
}