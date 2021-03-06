#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8
struct MeshT;
namespace math { class float4x4; class OBB; class Frustum; }
class ComponentCamera;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	
	void RenderMesh(MeshT mesh,math::float4x4 transform, uint tex_id);
	void RenderDebugAABB(math::OBB box);
	void RenderDebugFrustrum(math::Frustum frus);
	void OnResize(int width, int height);
	void RefreshProjection();
	bool GetVSync() const;
	void SetVSync(bool vsync);
public:
	bool vsync;
	ComponentCamera* active_camera = nullptr;
	uint my_id = 0;
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};