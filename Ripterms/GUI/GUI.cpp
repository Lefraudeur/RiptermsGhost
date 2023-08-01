#include "GUI.h"
#include <Windows.h>
#include <iostream>
#include "MinHook.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_win32.h>
#include <gl/GL.h>
#include "../Cache/Cache.h"

typedef BOOL(*type_wglSwapBuffers)(HDC);
FARPROC target_wglSwapBuffers = nullptr;
type_wglSwapBuffers original_wglSwapBuffers = nullptr;
WNDPROC original_WndProc = nullptr;
bool draw = false;

BOOL detour_wglSwapBuffers(HDC unnamedParam1)
{
	static HGLRC old_context = nullptr;
	static HGLRC new_context = nullptr;
	static bool isInit = false;
	static GLint last_viewport[4];

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	if (!isInit || viewport[2] != last_viewport[2] || viewport[3] != last_viewport[3]) {
		memcpy(last_viewport, viewport, sizeof(GLint) * 4);
		old_context = wglGetCurrentContext();
		if (new_context) {
			wglDeleteContext(new_context);
			new_context = nullptr;
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
		}
		new_context = wglCreateContext(unnamedParam1);
		/*
		wglMakeCurrent(unnamedParam1, new_context);
		glViewport(0, 0, viewport[2], viewport[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		*/

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(Ripterms::window);
		ImGui_ImplOpenGL3_Init();
		isInit = true;
	}

	wglMakeCurrent(unnamedParam1, new_context);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (draw) {
		ImGui::Begin("OpenGL-Hk");
		{
			ImGui::Text("Hello, World!");
		}
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	wglMakeCurrent(unnamedParam1, old_context);
	return original_wglSwapBuffers(unnamedParam1);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT detour_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYDOWN && wParam == VK_INSERT) {
		draw = !draw;
	}
	if (draw) ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

	return CallWindowProcA(original_WndProc, hWnd, msg, wParam, lParam);
}

bool Ripterms::GUI::init()
{
	HMODULE opengl32dll = GetModuleHandleA("opengl32.dll");
	if (!opengl32dll) return false;
	target_wglSwapBuffers = GetProcAddress(opengl32dll, "wglSwapBuffers");
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
	MH_DisableHook(target_wglSwapBuffers);
	MH_RemoveHook(target_wglSwapBuffers);
	SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	return;
}
