#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{

	bool ret = true;


	// Cube by triangles with buffer -----------------
	/*float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;

	float mx = x * 0.5f;
	float my = y * 0.5f;
	float mz = z * 0.5f;

	static const GLfloat g_vertex_data[] = {
		4-mx, -my, -mz,
		4-mx, my, -mz,
		4mx, -my, -mz,
		4mx, -my, -mz,
		4-mx, my, -mz,
		4mx, my, -mz,
		4mx, -my, -mz,
		4mx, my, -mz,
		4mx, -my, mz,
		4mx, -my, mz,
		4mx, my, -mz,
		4mx, my, mz,
		4-mx, -my, mz,
		4mx, -my, mz,
		4mx, my, mz,
		4-mx, -my, mz,
		4mx, my, mz,
		4-mx, my, mz,
		4-mx, -my, -mz,
		4-mx, -my, mz,
		4-mx, my, mz,
		4-mx, -my, -mz,
		4-mx, my, mz,
		4-mx, my, -mz,
		4mx, my, mz,
		4mx, my, -mz,
		4-mx, my, -mz,
		4mx, my, mz,
		4-mx, my, -mz,
		4-mx, my, mz,
		4-mx, -my, mz,
		4-mx, -my, -mz,
		4mx, -my, -mz,
		4-mx, -my, mz,
		4mx, -my, -mz,
		4mx, -my, mz };

	my_id = 0;
	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, g_vertex_data, GL_STATIC_DRAW);*/

	// Cube by triangles with  buffer and indices -----------------
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;

	float mx = x * 0.5f;
	float my = y * 0.5f;
	float mz = z * 0.5f;

	static const GLfloat g_vertex_data[] = 
	{
		mx, my, mz,
		mx, my, -mz,
		mx, -my, mz,
		mx, -my, -mz,
		-mx, -my, -mz,
		-mx, -my, mz,
		-mx, my, -mz,
		-mx, my, mz,
	};
	static const uint g_index_data[] =
	{
		4, 6, 3,
		3, 6, 1,
		3, 1, 2,
		2, 1, 0,
		5, 2, 0,
		5, 0, 7,
		4, 5, 7,
		4, 7, 6,
		0, 1, 6,
		0, 6, 7,
		6, 5, 3,
		6, 3, 2,
	};
	my_id = 0;
	my_indices = 0;
	glGenBuffers(1, (GLuint*) &(my_id));

	glBindBuffer(GL_ARRAY_BUFFER, my_id);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*3, g_vertex_data, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*) &(my_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*36, g_index_data, GL_STATIC_DRAW);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
update_status ModuleSceneIntro::PreUpdate(float dt)
{	
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	Plane(0, 1, 0, 0).Render();

//Cube with 2 buffers
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);

	/**
	// Cube by triangles -----------------
	float x = 2.0f;
	float y = 2.0f;
	float z = 2.0f;

	float mx = x * 2.5f;
	float my = y * 2.5f;
	float mz = z * 2.5f;

	glBegin(GL_TRIANGLES);
	// Face -Z -------------------
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(-mx, my, -mz);
	glVertex3f(mx, -my, -mz);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(mx, -my, -mz);
	glVertex3f(-mx, my, -mz);
	glVertex3f(mx, my, -mz);

	// Face X -------------------
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(mx, -my, -mz);
	glVertex3f(mx, my, -mz);
	glVertex3f(mx, -my, mz);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(mx, -my, mz);
	glVertex3f(mx, my, -mz);
	glVertex3f(mx, my, mz);

	// Face Z -------------------
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(mx, -my, mz);
	glVertex3f(mx, my, mz);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(mx, my, mz);
	glVertex3f(-mx, my, mz);

	// Face -X ------------------
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(-mx, -my, mz);
	glVertex3f(-mx, my, mz);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(-mx, my, mz);
	glVertex3f(-mx, my, -mz);

	// Face Y -------------------
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(mx, my, mz);
	glVertex3f(mx, my, -mz);
	glVertex3f(-mx, my, -mz);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(mx, my, mz);
	glVertex3f(-mx, my, -mz);
	glVertex3f(-mx, my, mz);

	// Face -Y ------------------
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(mx, -my, -mz);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(mx, -my, -mz);
	glVertex3f(mx, -my, mz);

	glEnd();

	glLineWidth(1.0f);
	
	*/
	return UPDATE_CONTINUE;
}
update_status ModuleSceneIntro::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}
void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}
