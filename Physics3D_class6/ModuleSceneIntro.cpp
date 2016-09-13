#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	ImGui_ImplSdlGL3_Init(App->window->window);

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
	//ImGui_ImplSdlGL3_NewFrame(App->window->window);
	
	return UPDATE_CONTINUE;
}
// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{/*
	static bool show_test_window = true;
	static bool show_another_window = false;
	static  ImVec4 clear_color = ImColor(114, 144, 154);
	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Test Window")) show_test_window ^= 1;
		if (ImGui::Button("Another Window")) show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
	
		if (show_test_window)
		{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
		}
		ImGui::Render();
		*/
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}
