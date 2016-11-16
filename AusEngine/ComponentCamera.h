#ifndef __COMPONENTCAMERA_H__
#define __COMPONENTCAMERA_H__

#include "Component.h"
#include "math.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* go);
	~ComponentCamera();

	bool Init();
	bool Update();
	void OnEditor();
	
	void SetFov(float fov);
	void SetAspectRatio(float w, float h);
	Frustum frustum;
private:
	float aspectRatio = 0.0f;
};



#endif // !__COMPONENTCAMERA_H__