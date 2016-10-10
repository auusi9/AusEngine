#include "ModuleGameObjectManager.h"
#include "GameObject.h"


ModuleGameObjectManager::ModuleGameObjectManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleGameObjectManager::~ModuleGameObjectManager()
{

}


bool ModuleGameObjectManager::Init()
{
	root = AddGameObject(nullptr);
	return true;
}

bool ModuleGameObjectManager::CleanUp()
{
	root->CleanUp();
	RELEASE(root);
	return true;
}

//Add A GameObject to the scene
GameObject* ModuleGameObjectManager::AddGameObject(GameObject* parent)
{
	if (parent == nullptr && parent != root)
		parent = root;

	GameObject* object = new GameObject(parent);
	parent->goChilds.push_back(object);

	return object;
}

update_status ModuleGameObjectManager::Update()
{

	root->Update();

	return UPDATE_CONTINUE;
}
