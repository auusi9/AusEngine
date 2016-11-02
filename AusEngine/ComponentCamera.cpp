#include "ComponentCamera.h"
#include "Imgui\imgui.h"
#include "GameObject.h"


ComponentCamera::ComponentCamera(GameObject* go) : Component(Camera, go)
{
}


ComponentCamera::~ComponentCamera()
{
}


bool ComponentCamera::Update()
{
	return true;
}


void ComponentCamera::OnEditor()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		
	}
}

Frustrum::Frustrum()
{
}

Frustrum::~Frustrum()
{
}
