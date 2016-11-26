#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include "Globals.h"
#include "Component.h"
#include "Math.h"
#include "Color.h"

class GameObject;

class ComponentCamera : public Component
{
	friend class ModuleAudio;
public:
	ComponentCamera(GameObject* container);
	~ComponentCamera();

	//void OnSave(Config& config) const override;
	//void OnLoad(Config* config) override;

	bool Init();
	bool Update();
	void OnUpdateTransform();
	void OnEditor();

	float GetNearPlaneDist() const;
	float GetFarPlaneDist() const;
	float GetFOV() const;
	float GetAspectRatio() const;

	void SetNearPlaneDist(float dist);
	void SetFarPlaneDist(float dist);
	void SetFOV(float fov);
	void SetHFOV(float fov);
	void SetAspectRatio(float aspect_ratio);

	void Look(const float3& position);
	
	float* GetOpenGLViewMatrix();
	float* GetOpenGLProjectionMatrix();

	bool ContainsAaBox(const math::AABB& refBox) const;
public:
	Frustum frustum;
	Color background;
	bool frustum_culling = false;
	bool projection_changed = false;
	const GameObject* looking_at = nullptr;
	uint looking_at_uid = 0;
};

#endif // __COMPONENT_CAMERA_H__