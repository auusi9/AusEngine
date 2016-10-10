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
#include "Assimp.h"

#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

#define checkImageWidth 64
#define checkImageHeight 64


using namespace std;
ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{

	bool ret = true;


	mesh = App->MeshD->Load("Assets/FBX/warrior.fbx") ;

	//Textures
	GLubyte checkImage[checkImageHeight][checkImageWidth][4];


	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
		checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		checkImage);


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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, g_vertex_data, GL_STATIC_DRAW);

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
	*/
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	aiDetachAllLogStreams();
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
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	
	// Cube by triangles -----------------
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;

	float mx = x * 0.5f;
	float my = y * 0.5f;
	float mz = z * 0.5f;

	glBegin(GL_TRIANGLES);

	// X -------------------
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, mz); //A
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, -mz); //D
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, mz);  //B

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, -mz); //C
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, -mz); //D
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, mz); //A


													 // Y -------------------
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, my, mz); //B
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, -mz); //D
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, -mz); //E

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, mz); //B
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, my, -mz); //E
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, mz); //F

													 // Z -------------------
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, mz); //G
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, mz); //A
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, mz); //B

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, -my, mz); //G
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, my, mz); //B
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, mz); //F

													 // -X ------------------
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, -mz);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, mz);

	// -Y ------------------
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, -my, -mz);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, mz);

	// -Z -------------------
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, -my, -mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, -mz);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, -mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, -mz);

	glEnd();
	
	
	for (vector<Mesh>::iterator item = mesh.begin(); item != mesh.end(); ++item)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*item).id_indices);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glDrawElements(GL_TRIANGLES, (*item).num_indices, GL_UNSIGNED_INT, NULL);
		glDisableClientState(GL_VERTEX_ARRAY);

	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
		return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}
