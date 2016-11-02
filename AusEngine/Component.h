#ifndef __COMPONENT_H__
#define __COMPONENT_H__


class GameObject;
enum componentType
{
	Transform,
	Meshes,
	Texture,
	Material,
	Camera
};

class Component
{
public:
	Component();
	Component(componentType _type, GameObject* go);
	~Component();

	componentType type;
	virtual bool Init();
	virtual void Active();
	virtual bool Update();
	virtual void OnEditor();
	GameObject* gameObject = nullptr;
private:
	bool active = true;
	
};

#endif // !__COMPONENT_H__