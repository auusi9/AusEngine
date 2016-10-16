#ifndef __MODULEGAMEOBJECTMANAGER_H__
#define __MODULEGAMEOBJECTMANAGER_H__

#include "Module.h"

class GameObject;

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

	void HierarchyPanel();
	void HierarchyShowChilds(GameObject* parent);

	void InspectorPanel();
	void InspectorShowComponents(GameObject* gameObject);
	GameObject* focus_go= nullptr;
private:
	
};

#endif //!__MODULEGAMEOBJECTMANAGER_H__
