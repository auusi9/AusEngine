#include "ComponentMaterial.h"
#include "Imgui\imgui.h"
#include "GameObject.h"


ComponentMaterial::ComponentMaterial(GameObject* go) : Component(Material, go)
{
}


ComponentMaterial::~ComponentMaterial()
{
}

//Renders the current Mesh
bool ComponentMaterial::Update()
{

	return true;
}

void ComponentMaterial::OnEditor()
{
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::Image((ImTextureID)textureId, ImVec2(250, 250));
	}
}
