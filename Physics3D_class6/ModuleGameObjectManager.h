#ifndef __MODULEGAMEOBJECTMANAGER_H__
#define __MODULEGAMEOBJECTMANAGER_H__

#include "Module.h"

class GameObject;

class ModuleGameObjectManager : public Module
{
public:
	ModuleGameObjectManager(Application* app, bool start_enabled = true);
	~ModuleGameObjectManager();
	GameObject* AddGameObject(GameObject* parent);

	GameObject* root;

	bool Init();
	bool CleanUp();
	update_status Update();

private:
	
};

#endif //!__MODULEGAMEOBJECTMANAGER_H__
