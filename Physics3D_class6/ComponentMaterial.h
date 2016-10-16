#ifndef __COMPONENTMATERIAL_H__
#define __COMPONENTMATERIAL_H__

#include "Component.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* go);
	~ComponentMaterial();

	componentType type;

	bool Update();
	void OnEditor();
	unsigned int textureId = 0;
private:
};

#endif // !__COMPONENTMATERIAL_H__