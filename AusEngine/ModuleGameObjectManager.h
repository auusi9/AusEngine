#ifndef __MODULEGAMEOBJECTMANAGER_H__
#define __MODULEGAMEOBJECTMANAGER_H__

#include "Module.h"

class GameObject;
class ComponentCamera;

class ModuleGameObjectManager : public Module
{
public:
	ModuleGameObjectManager(Application* app, bool start_enabled = true);
	~ModuleGameObjectManager();
	
	GameObject* root;

	bool Init();
	bool CleanUp();
	update_status Update(float dt);

	GameObject* AddGameObject(GameObject* parent);
	bool RemoveGameObject(GameObject* go);
	void DrawSceneGameObjects(GameObject* go);
	void HierarchyPanel();
	void HierarchyShowChilds(GameObject* parent);

	void InspectorPanel();
	ComponentCamera* toTest;
	GameObject* focusGo= nullptr;
private:
	uint numObjects = 0;
	
};

#endif //!__MODULEGAMEOBJECTMANAGER_H__
