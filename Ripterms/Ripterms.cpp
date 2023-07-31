#include "Ripterms.h"
#include <Windows.h>
#include <psapi.h>
#include <iostream>

void mainLoop()
{

}

typedef void(*nglClearType)(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer);

nglClearType originalnglClear = nullptr;

nglClearType targetnglClear = nullptr;

bool tmp_no_hook = false;

void detournglClear(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer)
{
	if (tmp_no_hook) return originalnglClear(env, clazz, mask, function_pointer);
	static bool runonce = true;
	if (runonce && env)
	{
		Ripterms::p_env = env;
		runonce = false;
	}
	if (GetAsyncKeyState(VK_END)) {
		tmp_no_hook = true;
		std::thread a([] {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			FreeLibrary(Ripterms::module);
		});
		if (a.joinable()) a.detach();
		return originalnglClear(env, clazz, mask, function_pointer);
	}
	mainLoop();
	return originalnglClear(env, clazz, mask, function_pointer);
}

struct Process
{
	DWORD pid;
	std::string windowName;
};

BOOL CALLBACK EnumWindowsCallback(_In_ HWND hwnd, _In_ LPARAM lParam)
{
	Process* p_process = (Process*)lParam;
	DWORD pid = 0;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == p_process->pid
		&& GetWindow(hwnd, GW_OWNER) == NULL
		&& IsWindowVisible(hwnd)
		&& GetConsoleWindow() != hwnd
		) {
		char str[64];
		GetWindowTextA(hwnd, str, 64);
		p_process->windowName = str;
		return FALSE;
	}
	return TRUE;
}

std::string getCurrentWindowName()
{
	Process process = { GetProcessId(GetCurrentProcess()) };
	EnumWindows(&EnumWindowsCallback, (LPARAM)&process);
	return process.windowName;
}

void Ripterms::init()
{
	if (getCurrentWindowName().find("Lunar Client 1.8.9") != std::string::npos) version = LUNAR_1_8_9;
	if (version == UNDEFINED) {
		std::cout << "unknown version" << std::endl;
		std::cin.ignore();
		FreeLibrary(module);
		return;
	}
	MH_Initialize();
	HMODULE lwjgl64dll = GetModuleHandleA("lwjgl64.dll");
	targetnglClear = reinterpret_cast<nglClearType>(GetProcAddress(lwjgl64dll, "Java_org_lwjgl_opengl_GL11_nglClear"));
	MH_STATUS status = MH_CreateHook(targetnglClear, detournglClear, reinterpret_cast<LPVOID*>(&originalnglClear));
	if (status != MH_OK)
	{
		std::cerr << MH_StatusToString(status) << std::endl;
		std::cin.ignore();
		FreeLibrary(module);
		return;
	}
	status = MH_EnableHook(targetnglClear);
	if (status != MH_OK)
	{
		std::cerr << MH_StatusToString(status) << std::endl;
		std::cin.ignore();
		FreeLibrary(module);
		return;
	}
}

void Ripterms::clean()
{
	MH_DisableHook(targetnglClear);
	MH_RemoveHook(targetnglClear);
	MH_Uninitialize();
}
