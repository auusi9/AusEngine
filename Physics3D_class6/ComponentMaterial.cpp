#include "ComponentMaterial.h"
#include "Imgui\imgui.h"
#include "GameObject.h"


ComponentMaterial::ComponentMaterial(GameObject* go) : Component(Material, go)
{
}


ComponentMaterial::~ComponentMaterial()
{
}


bool ComponentMaterial::Update()
{
	return true;
}

//If there is a texture, shows the Image on the Inspector
void ComponentMaterial::OnEditor()
{
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::Image((ImTextureID)textureId, ImVec2(200, 200));
	}
}
