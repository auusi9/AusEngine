#ifndef __COMPONENTMATERIAL_H__
#define __COMPONENTMATERIAL_H__

#include "Component.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* go);
	~ComponentMaterial();

	bool Update();
	void OnEditor();
	unsigned int textureId = 0;
};

#endif // !__COMPONENTMATERIAL_H__