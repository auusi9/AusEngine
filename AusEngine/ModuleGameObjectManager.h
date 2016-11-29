#ifndef __MODULEGAMEOBJECTMANAGER_H__
#define __MODULEGAMEOBJECTMANAGER_H__

#include "Module.h"
#include "Quadtree.h"
class GameObject;
class ComponentCamera;


class ModuleGameObjectManager : public Module
{
public:
	ModuleGameObjectManager(Application* app, bool start_enabled = true);
	~ModuleGameObjectManager();
	
	GameObject* root;

	bool Init();
	bool Start();
	bool CleanUp();
	update_status Update(float dt);

	GameObject* AddGameObject(GameObject* parent);
	bool RemoveGameObject(GameObject* go);
	void DrawSceneGameObjects();
	void HierarchyPanel();
	void HierarchyShowChilds(GameObject* parent);
	void InsertOnQuadTree(GameObject* go);

	void InspectorPanel();
	ComponentCamera* toTest;
	GameObject* focusGo= nullptr;
private:
	uint numObjects = 0;
	Quadtree quad;
};

#endif //!__MODULEGAMEOBJECTMANAGER_H__
