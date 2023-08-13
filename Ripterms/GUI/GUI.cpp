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

namespace {
	typedef BOOL(WINAPI* type_wglSwapBuffers)(HDC);
	type_wglSwapBuffers original_wglSwapBuffers = nullptr;
	WNDPROC original_WndProc = nullptr;
	type_wglSwapBuffers target_wglSwapBuffers = nullptr;

	bool hook = true;
	bool stop = false;
}

BOOL WINAPI detour_wglSwapBuffers(HDC unnamedParam1)
{
	static HGLRC new_context = nullptr;
	if (!hook) {
		return original_wglSwapBuffers(unnamedParam1);
	}
	static bool isInit = false;
	static HGLRC old_context = nullptr;

	static RECT originalClip;
	static bool clipped = true;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	if (!isInit) {
		old_context = wglGetCurrentContext();
		new_context = wglCreateContext(unnamedParam1);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;


		ImFontConfig CustomFont;
		CustomFont.FontDataOwnedByAtlas = false;

		io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 17.5f, &CustomFont);
		io.Fonts->AddFontDefault(); ImGui::StyleColorsDark();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	//	ImGui::StyleColorsDark();
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
		/* colors  */

		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_CheckMark] = ImColor(173, 55, 65);
		style.Colors[ImGuiCol_CheckMarkOn] = ImColor(10, 150, 10);
		style.Colors[ImGuiCol_SliderGrab] = ImColor(10, 150, 10);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(10, 150, 10);
		style.Colors[ImGuiCol_SliderLine] = ImColor(173, 55, 65);
		style.Colors[ImGuiCol_FrameBg] = ImColor(25, 25, 25);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 25);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 25);
		style.Colors[ImGuiCol_WindowBg] = ImColor(11, 14, 15);
		style.Colors[ImGuiCol_Button] = ImColor(31, 30, 31);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(173, 55, 65);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(239, 73, 88);
		style.Colors[ImGuiCol_Header] = ImColor(78, 78, 78);
		style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200);
		style.Colors[ImGuiCol_HeaderActive] = ImColor(78, 78, 78);
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(78, 78, 78);

		/*  rounding */

		style.FrameRounding = 10.f;
		style.WindowRounding = 5.f;
		style.ChildRounding = 5.f;
		style.GrabRounding = 5.f;
		style.PopupRounding = 5.f;
		style.ScrollbarRounding = 5.f;
		style.TabRounding = 5.f;

		if (clipped)
		{
			GetClipCursor(&originalClip);
			ClipCursor(nullptr);
			clipped = false;
		}
		ImGui::SetNextWindowSizeConstraints(ImVec2(400.0f, 300.0f), ImVec2(400.0f, 1000.0f));
		ImGui::Begin("Ripterms Ghost", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
		{
			ImGui::SetWindowSize(ImVec2(400.0f, 300.0f));
			
			Ripterms::Modules::AimAssist::renderGUI();
			Ripterms::Modules::Reach::renderGUI();
			Ripterms::Modules::LeftClicker::renderGUI();
			Ripterms::Modules::FullBright::renderGUI();
			Ripterms::Modules::ClientBrandChanger::renderGUI();
			Ripterms::Modules::Test::renderGUI();
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

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK detour_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYDOWN && wParam == VK_INSERT) {
		Ripterms::GUI::draw = !Ripterms::GUI::draw;
	}
	if (Ripterms::GUI::draw) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProcA(original_WndProc, hWnd, msg, wParam, lParam);
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
	SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	return;
}
