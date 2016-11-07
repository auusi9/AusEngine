#ifndef __COMPONENTCAMERA_H__
#define __COMPONENTCAMERA_H__

#include "Component.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* go);
	~ComponentCamera();

	bool Update();
	void OnEditor();
	
};



#endif // !__COMPONENTCAMERA_H__