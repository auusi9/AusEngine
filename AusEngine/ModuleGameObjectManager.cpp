#include "ModuleGameObjectManager.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"
#include "Imgui\imgui.h"
#include "ModuleCamera3D.h"
#include <vector>
#include <string>
using namespace std;

ModuleGameObjectManager::ModuleGameObjectManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleGameObjectManager::~ModuleGameObjectManager()
{
}


bool ModuleGameObjectManager::Init()
{
	root = new GameObject(nullptr);
	return true;
}

bool ModuleGameObjectManager::CleanUp()
{
	root->CleanUp();
	RELEASE(root);
	return true;
}

update_status ModuleGameObjectManager::Update(float dt)
{
	root->Update();
	DrawSceneGameObjects(root);
	HierarchyPanel();
	InspectorPanel();
	return UPDATE_CONTINUE;
}

//Add A GameObject to the scene
GameObject* ModuleGameObjectManager::AddGameObject(GameObject* parent)
{
	if (parent == nullptr)
		parent = root;

	GameObject* object;

		object = new GameObject(parent);
		parent->goChilds.push_back(object);
		numObjects++;
		object->name += std::to_string(numObjects);
	return object;
}

//Removes a specific gameObject from the scene
bool ModuleGameObjectManager::RemoveGameObject(GameObject* go)
{
	numObjects--;
	return go->root->RemoveChild(go);
}

void ModuleGameObjectManager::DrawSceneGameObjects(GameObject* go)
{
	for (vector<GameObject*>::iterator item = go->goChilds.begin(); item != go->goChilds.end(); ++item)
	{
		DrawSceneGameObjects(*item);	
	}
	if (go->mesh != nullptr)
	{
		if (/*App->camera->GetDummy()*/toTest->ContainsAaBox(go->transform->GetAABB()))
		{
			go->mesh->OnDraw();
		}
	}

}

void ModuleGameObjectManager::HierarchyPanel()
{
	ImGui::Begin("Hierarchy");

	for (vector<GameObject*>::iterator item = root->goChilds.begin(); item != root->goChilds.end(); ++item)
		HierarchyShowChilds(*item);

	ImGui::End();
}

//Recursive function to show all gameObjects in tree form in Hierarchy window
void ModuleGameObjectManager::HierarchyShowChilds(GameObject* gameObject)
{
		uint flag = 0;

		if (focusGo == gameObject)
			flag |= ImGuiTreeNodeFlags_Selected;

		if (gameObject->goChilds.size() == 0)
			flag |= ImGuiTreeNodeFlags_Bullet;

		if (ImGui::TreeNodeEx(gameObject->name.data(), flag))
		{
			if (ImGui::IsItemClicked(0))
			{
				focusGo = gameObject;
			}

			for (vector<GameObject*>::iterator item = gameObject->goChilds.begin(); item != gameObject->goChilds.end(); ++item)
				HierarchyShowChilds(*item);

			ImGui::TreePop();
		}
}

void ModuleGameObjectManager::InspectorPanel() 
{
	ImGui::Begin("Inspector");

	if (focusGo != nullptr)
	{
		for (vector<Component*>::iterator item = focusGo->Components.begin(); item != focusGo->Components.end(); ++item)
			(*item)->OnEditor();
	}

	ImGui::End();
}
