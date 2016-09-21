#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Imgui\GL\gl3w.h"

ModuleImGui::ModuleImGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleImGui::~ModuleImGui()
{}

// Load assets
bool ModuleImGui::Init()
{
	bool ret = true;
	gl3wInit();

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
update_status ModuleImGui::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);

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

