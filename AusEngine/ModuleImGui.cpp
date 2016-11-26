#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"
#pragma comment (lib, "Glew/libx86/glew32.lib")

ModuleImGui::ModuleImGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleImGui::~ModuleImGui()
{}

// Load assets
bool ModuleImGui::Init()
{
	bool ret = true;
	glewInit();

	ImGui_ImplSdlGL3_Init(App->window->window);
	return ret;
}

// Clean up ImGui
bool ModuleImGui::CleanUp()
{
	LOG("Unloading Intro scene");
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}

void ModuleImGui::HandleInput(SDL_Event * event)
{
	ImGui_ImplSdlGL3_ProcessEvent(event);
}

bool ModuleImGui::UsingKeyboard()
{
	return capture_keyboard;
}

bool ModuleImGui::UsingMouse()
{
	return capture_mouse;
}

update_status ModuleImGui::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	ImGuiIO& io = ImGui::GetIO();
		capture_keyboard = io.WantCaptureKeyboard;
		capture_mouse = io.WantCaptureMouse;
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleImGui::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	static bool show_test_window = true;
	static bool show_menu = true;

	if (show_menu == true)
	{
		if (ImGui::BeginMainMenuBar())
		{
			bool selected = false;
			if (ImGui::BeginMenu("File"))
			{
				/*ImGui::MItenuItem("New");
				ImGui::Menuem("Save");*/
				
				if (ImGui::MenuItem("Quit"))
					ret = UPDATE_STOP;

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Open test window"))
				{
					if (show_test_window)
						show_test_window = false;
					else
						show_test_window = true;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
	ImGui::Render();

	return ret;
}

