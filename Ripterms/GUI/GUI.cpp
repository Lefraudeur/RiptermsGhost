#include "GUI.h"
#include <Windows.h>
#include <iostream>
#include "MinHook.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_win32.h>
#include <gl/GL.h>
#include "../Cache/Cache.h"
#include "../Modules/Modules.h"
#include "font.h"

namespace
{
	typedef BOOL(WINAPI* type_wglSwapBuffers)(HDC);
	type_wglSwapBuffers original_wglSwapBuffers = nullptr;
	WNDPROC original_WndProc = nullptr;
	type_wglSwapBuffers target_wglSwapBuffers = nullptr;

	ImGuiContext* imGuiContext = nullptr;
	HGLRC new_context = nullptr;

	bool hook = true;
}

void update_style()
{
	/* colors  */

	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_CheckMark] = Ripterms::GUI::color_bool_disabled;
	style.Colors[ImGuiCol_CheckMarkOn] = Ripterms::GUI::color_bool_enabled;
	style.Colors[ImGuiCol_SliderGrab] = Ripterms::GUI::color_slider_grab;
	style.Colors[ImGuiCol_SliderGrabActive] = Ripterms::GUI::color_slider_grab;
	style.Colors[ImGuiCol_SliderLine] = Ripterms::GUI::color_slider_line;
	style.Colors[ImGuiCol_FrameBg] = Ripterms::GUI::color_frame_bg;
	style.Colors[ImGuiCol_FrameBgActive] = Ripterms::GUI::color_frame_bg_active;
	style.Colors[ImGuiCol_FrameBgHovered] = Ripterms::GUI::color_frame_bg_hovered;
	style.Colors[ImGuiCol_WindowBg] = Ripterms::GUI::color_window_bg;
	style.Colors[ImGuiCol_Button] = Ripterms::GUI::color_button;
	style.Colors[ImGuiCol_ButtonHovered] = Ripterms::GUI::color_button_hovered;
	style.Colors[ImGuiCol_ButtonActive] = Ripterms::GUI::color_button_active;
	style.Colors[ImGuiCol_Header] = Ripterms::GUI::color_header;
	style.Colors[ImGuiCol_Text] = Ripterms::GUI::color_text;
	style.Colors[ImGuiCol_HeaderActive] = Ripterms::GUI::color_header_active;
	style.Colors[ImGuiCol_HeaderHovered] = Ripterms::GUI::color_header_hovered;
	style.Colors[ImGuiCol_ChildBg] = Ripterms::GUI::color_child_bg;

	/*  rounding */

	style.FrameRounding = Ripterms::GUI::rounding_frame;
	style.WindowRounding = Ripterms::GUI::rounding_window;
	style.ChildRounding = Ripterms::GUI::rounding_child;
	style.GrabRounding = Ripterms::GUI::rounding_grab;
	style.PopupRounding = Ripterms::GUI::rounding_popup;
	style.ScrollbarRounding = Ripterms::GUI::rounding_scrollbar;
	style.TabRounding = Ripterms::GUI::rounding_tab;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK detour_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYDOWN && wParam == VK_INSERT)
	{
		Ripterms::GUI::draw = !Ripterms::GUI::draw;
	}
	if (Ripterms::GUI::draw)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProcA(original_WndProc, hWnd, msg, wParam, lParam);
}

BOOL WINAPI detour_wglSwapBuffers(HDC unnamedParam1)
{
	if (!hook)
	{
		return original_wglSwapBuffers(unnamedParam1);
	}
	static bool isInit = false;
	static HGLRC old_context = nullptr;

	static RECT originalClip;
	static bool clipped = true;

	HWND current_window = WindowFromDC(unnamedParam1);
	if (isInit && current_window != Ripterms::window)
	{
		old_context = wglGetCurrentContext();
		wglMakeCurrent(unnamedParam1, new_context);
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext(imGuiContext);
		SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
		Ripterms::window = current_window;
		original_WndProc = (WNDPROC)SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)&detour_WndProc);
		wglMakeCurrent(unnamedParam1, old_context);
		isInit = false;
	}

	if (!isInit)
	{
		old_context = wglGetCurrentContext();
		if (new_context)
			wglDeleteContext(new_context);
		new_context = wglCreateContext(unnamedParam1);

		imGuiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;


		ImFontConfig CustomFont;
		CustomFont.FontDataOwnedByAtlas = false;

		io.Fonts->AddFontFromMemoryTTF((void*)Custom.data(), (int)Custom.size(), 17.5f, &CustomFont);
		io.Fonts->AddFontDefault(); ImGui::StyleColorsDark();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		//ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplWin32_Init(Ripterms::window);
		isInit = true;
	}

	wglMakeCurrent(unnamedParam1, new_context);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (Ripterms::GUI::draw)
	{
		update_style();

		if (clipped)
		{
			GetClipCursor(&originalClip);
			ClipCursor(nullptr);
			clipped = false;
		}

		ImGui::SetNextWindowBgAlpha(.8f);
		ImGui::SetWindowSize(ImVec2(600.0f, 400.f));
		ImGui::SetNextWindowSizeConstraints(ImVec2(600.f, 400.f), ImVec2(600.f, 1000.f));
		ImGui::Begin("Ripterms Ghost", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
		{

			ImGui::SetWindowSize(ImVec2(600.f, 400.f));
		
		
			ImVec2 window_size = ImGui::GetWindowSize();
			ImVec2 center_pos = ImVec2(window_size.x * .5f, window_size.y * .5f);

			ImGui::BeginChild("##header", (ImVec2(583, 40)));
			
			/* text animation */

			if (Ripterms::GUI::tick || Ripterms::GUI::alpha >= 255)
			{
				Ripterms::GUI::tick = true;
				if (!(Ripterms::GUI::alpha <= 0))
					Ripterms::GUI::alpha -= Ripterms::GUI::speed;
				else if (Ripterms::GUI::alpha <= 0)
					Ripterms::GUI::tick ^= 1;
			}

			else if (!Ripterms::GUI::tick || Ripterms::GUI::alpha != 255)
			{
				Ripterms::GUI::tick = false;
				if (!(Ripterms::GUI::alpha >= 255))
					Ripterms::GUI::alpha += Ripterms::GUI::speed;
				else if (Ripterms::GUI::alpha >= 255)
					Ripterms::GUI::tick ^= 1;
			}

			if(Ripterms::GUI::ripterms_title)
			{
				ImGui::SetCursorPosY(10);
				ImGui::SetCursorPosX(center_pos.x - 55);
				ImGui::TextColored
				(
					ImColor
					(
						111,	0, 15,
						(int)Ripterms::GUI::alpha
					),
					"r i p t e r m s    g h o s t"
				);
			}
			ImGui::EndChild();

			static std::string current_tab = "Combat";
			ImGui::SetCursorPosY(55);
			ImGui::BeginChild("##categories", ImVec2(100, 345), 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.f);

				for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
				{
					bool is_selected = category.first == current_tab;
					if(is_selected) 
						ImGui::PushStyleColor(ImGuiCol_Button, Ripterms::GUI::color_active_tab);
					if (ImGui::Button(category.first.c_str(), Ripterms::GUI::category_button_size))
						current_tab = category.first;
					if (is_selected)
						ImGui::PopStyleColor();
				}

				ImGui::SetCursorPos(ImVec2(0, ImGui::GetWindowSize()[1] - Ripterms::GUI::category_button_size[1]));

				if (current_tab == "Settings") { ImGui::PushStyleColor(ImGuiCol_Button, Ripterms::GUI::color_active_tab); }
				if (ImGui::Button("Settings", Ripterms::GUI::category_button_size)) { current_tab = "Settings"; }
				if (current_tab == "Settings") { ImGui::PopStyleColor(); }

				ImGui::PopStyleVar();
			}
			ImGui::EndChild();

			ImGui::SameLine();
		
			ImGui::SetCursorPosX(115);
			ImGui::BeginChild("##modules");
			{
				if (current_tab == "Settings")
				{
					ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));

					ImGui::SetCursorPos(ImVec2(4, 2));
					ImGui::Text("Settings");
					ImGui::Separator();	
				
					ImGui::Checkbox("Ripterms Title", &Ripterms::GUI::ripterms_title);
					ImGui::Checkbox("Show Color Theming", &Ripterms::GUI::show_color_theming);
					ImGui::Checkbox("Show Rounding Theming", &Ripterms::GUI::show_rounding_theming);

					if(Ripterms::GUI::show_color_theming)
					{
						ImGui::Separator();

						ImGui::ColorEdit4("Active Tab", &Ripterms::GUI::color_active_tab.x, ImGuiColorEditFlags_NoInputs);
						//ImGui::ColorEdit4("Inactive Tab", &Ripterms::GUI::color_inactive_tab.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Child Background", &Ripterms::GUI::color_child_bg.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Bool Enabled", &Ripterms::GUI::color_bool_enabled.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Bool Disabled", &Ripterms::GUI::color_bool_disabled.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Slider Grab", &Ripterms::GUI::color_slider_grab.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Slider Line", &Ripterms::GUI::color_slider_line.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Frame Background", &Ripterms::GUI::color_frame_bg.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Frame Background Active", &Ripterms::GUI::color_frame_bg_active.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Frame Background Hovered", &Ripterms::GUI::color_frame_bg_hovered.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Window Background", &Ripterms::GUI::color_window_bg.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Button", &Ripterms::GUI::color_button.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Button  Active", &Ripterms::GUI::color_button_active.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Button Hovered", &Ripterms::GUI::color_button_hovered.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Text", &Ripterms::GUI::color_text.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Header", &Ripterms::GUI::color_header.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Header Active", &Ripterms::GUI::color_header_active.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Header Hovered", &Ripterms::GUI::color_header_hovered.Value.x, ImGuiColorEditFlags_NoInputs);
					}
				
					if (Ripterms::GUI::show_rounding_theming)
					{
						ImGui::Separator();

						ImGui::SliderFloat("Frame ##Rounding", &Ripterms::GUI::rounding_frame, 0, 100, "%1.0f");
						ImGui::SliderFloat("Window ##Rounding", &Ripterms::GUI::rounding_window, 0, 100, "%1.0f");
						ImGui::SliderFloat("Child ##Rounding", &Ripterms::GUI::rounding_child, 0, 100, "%1.0f");
						ImGui::SliderFloat("Grab ##Rounding", &Ripterms::GUI::rounding_grab, 0, 100, "%1.0f");
						ImGui::SliderFloat("Popup ##Rounding", &Ripterms::GUI::rounding_popup, 0, 100, "%1.0f");
						ImGui::SliderFloat("Scrollbar ##Rounding", &Ripterms::GUI::rounding_scrollbar, 0, 100, "%1.0f");
						ImGui::SliderFloat("Tab ##Rounding", &Ripterms::GUI::rounding_tab, 0, 100, "%1.0f");
					}
					ImGui::PopStyleVar(2);
				}
				else
				{
					ImGui::SetCursorPos(ImVec2(4, 2));
					ImGui::Text(current_tab.c_str());
					ImGui::Separator();

					for (Ripterms::Modules::IModule* module : Ripterms::Modules::categories[current_tab])
					{
						module->renderGUI();
					}
				}
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}
	else if (!clipped)
	{
		ClipCursor(&originalClip);
		clipped = true;
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	wglMakeCurrent(unnamedParam1, old_context);
	return original_wglSwapBuffers(unnamedParam1);
}

bool Ripterms::GUI::init()
{
	HMODULE opengl32dll = GetModuleHandleA("opengl32.dll");
	if (!opengl32dll) return false;
	target_wglSwapBuffers = reinterpret_cast<type_wglSwapBuffers>(GetProcAddress(opengl32dll, "wglSwapBuffers"));
	MH_STATUS status = MH_CreateHook(target_wglSwapBuffers, &detour_wglSwapBuffers, reinterpret_cast<LPVOID*>(&original_wglSwapBuffers));
	if (status != MH_OK)
	{
		std::cerr << MH_StatusToString(status) << std::endl;
		return false;
	}
	status = MH_EnableHook(target_wglSwapBuffers);
	if (status != MH_OK)
	{
		std::cerr << MH_StatusToString(status) << std::endl;
		return false;
	}
	original_WndProc = (WNDPROC)SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)&detour_WndProc);
	return true;
}

void Ripterms::GUI::clean()
{
	draw = false;
	hook = false;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext(imGuiContext);
	SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
	wglDeleteContext(new_context);
	return;
}
