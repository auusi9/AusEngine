#include "ModuleGameObjectManager.h"
#include "GameObject.h"
#include "Component.h"
#include "Imgui\imgui.h"
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

	return object;
}

//Removes a specific gameObject from the scene
bool ModuleGameObjectManager::RemoveGameObject(GameObject* go)
{
	return go->root->RemoveChild(go);
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

		if (focus_go == gameObject)
			flag = ImGuiTreeNodeFlags_Selected;

		if (gameObject->goChilds.size() == 0)
			flag |= ImGuiTreeNodeFlags_Leaf;
		

			if (ImGui::TreeNodeEx(gameObject->name.data(), flag | ImGuiTreeNodeFlags_OpenOnArrow))
			{
				if (ImGui::IsItemClicked(0))
				{
					focus_go = gameObject;
				}
				for (vector<GameObject*>::iterator item = gameObject->goChilds.begin(); item != gameObject->goChilds.end(); ++item)
					HierarchyShowChilds(*item);

				ImGui::TreePop();
			}
}

void ModuleGameObjectManager::InspectorPanel() 
{
	ImGui::Begin("Inspector");

	if(focus_go != nullptr)
		InspectorShowComponents(focus_go);

	ImGui::End();

}

void ModuleGameObjectManager::InspectorShowComponents(GameObject* gameObject)
{
	for (vector<Component*>::iterator item = gameObject->Components.begin(); item != gameObject->Components.end(); ++item)
		(*item)->OnEditor();
}