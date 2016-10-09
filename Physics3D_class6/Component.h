#ifndef __COMPONENT_H__
#define __COMPONENT_H__

enum componentType
{
	Transform,
	Mesh,
	Texture,
	Material
};

class Component
{
public:
	Component();
	Component(componentType _type);
	~Component();

	componentType type;
	virtual bool Init();
	virtual void Active();
	virtual bool Update();

private:
	bool active = true;
};

#endif // !__COMPONENT_H__