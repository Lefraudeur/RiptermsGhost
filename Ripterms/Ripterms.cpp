#include "Ripterms.h"
#include <psapi.h>
#include <iostream>
#include "Cache/Cache.h"
#include "GUI/GUI.h"
#include "Modules/Modules.h"
#include "JavaClass/JavaClass.h"
#include <MinHook.h>

void mainLoop()
{
	if (!Ripterms::cache->fillCache()) return;
	Ripterms::Modules::AimAssist::run();
}

typedef void(JNICALL* nglClearType)(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer);
nglClearType originalnglClear = nullptr;
nglClearType targetnglClear = nullptr;

typedef void(JNICALL* glClearType)(JNIEnv* env, jclass clazz, jint mask);
glClearType originalglClear = nullptr;
glClearType targetglClear = nullptr;

bool tmp_no_hook = false;

void JNICALL detournglClear(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer)
{
	static bool runMainLoop = false;

	if (tmp_no_hook) {
		if (Ripterms::cache) {
			if (Ripterms::p_tienv) Ripterms::p_tienv->DisposeEnvironment();
			delete Ripterms::cache;
			delete Ripterms::classcache;
			Ripterms::cache = nullptr;
		}
		return originalnglClear(env, clazz, mask, function_pointer);
	}

	static bool runonce = true;
	if (runonce)
	{
		Ripterms::p_env = env;
		env->GetJavaVM(&Ripterms::p_jvm);
		Ripterms::p_jvm->GetEnv((void**)&Ripterms::p_tienv, JVMTI_VERSION);
		runMainLoop = Ripterms::classcache->fillCache();
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
	if (runMainLoop) mainLoop();
	return originalnglClear(env, clazz, mask, function_pointer);
}

void JNICALL detourglClear(JNIEnv* env, jclass clazz, jint mask)
{
	static bool runMainLoop = false;

	if (tmp_no_hook) {
		if (Ripterms::cache) {
			if (Ripterms::p_tienv) Ripterms::p_tienv->DisposeEnvironment();
			delete Ripterms::cache;
			delete Ripterms::classcache;
			Ripterms::cache = nullptr;
		}
		return originalglClear(env, clazz, mask);
	}

	static bool runonce = true;
	if (runonce)
	{
		Ripterms::p_env = env;
		env->GetJavaVM(&Ripterms::p_jvm);
		Ripterms::p_jvm->GetEnv((void**)&Ripterms::p_tienv, JVMTI_VERSION);
		runMainLoop = Ripterms::classcache->fillCache();
		runonce = false;
	}
	if (GetAsyncKeyState(VK_END)) {
		tmp_no_hook = true;
		std::thread a([] {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			FreeLibrary(Ripterms::module);
		});
		if (a.joinable()) a.detach();
		return originalglClear(env, clazz, mask);
	}
	if (runMainLoop) mainLoop();
	return originalglClear(env, clazz, mask);
}

struct Process
{
	DWORD pid;
	HWND window;
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
		p_process->window = hwnd;
		return FALSE;
	}
	return TRUE;
}

HWND getCurrentWindow()
{
	HANDLE current = GetCurrentProcess();
	Process process = { GetProcessId(current) };
	CloseHandle(current);
	EnumWindows(&EnumWindowsCallback, (LPARAM)&process);
	return process.window;
}

std::string getWindowName(HWND hwnd)
{
	char str[64];
	GetWindowTextA(hwnd, str, 64);
	return std::string(str);
}


BOOL Ripterms::init()
{
	Ripterms::window = getCurrentWindow();
	std::string windowName = getWindowName(window);
	if (windowName.find("Lunar Client 1.8.9") != std::string::npos) {
		version = LUNAR_1_8_9;
		majorVersion = MAJOR_1_8_9;
	}
	else if (windowName.find("Lunar Client 1.7.10") != std::string::npos) {
		version = LUNAR_1_7_10;
		majorVersion = MAJOR_1_8_9;
	}
	else if (windowName.find("Lunar Client 1.16.5") != std::string::npos) {
		version = LUNAR_1_16_5;
		majorVersion = MAJOR_1_16_5;
	}
	else if (windowName.find("Paladium") != std::string::npos || windowName.find("Minecraft 1.7.10") != std::string::npos) {
		version = FORGE_1_7_10;
		majorVersion = MAJOR_1_8_9;
	}
	else {
		std::cerr << "unknown version" << std::endl;
		return FALSE;
	}
	MH_Initialize();
	if (majorVersion == MAJOR_1_8_9) {
		HMODULE lwjgl64dll = GetModuleHandleA("lwjgl64.dll");
		if (!lwjgl64dll) return FALSE;
		targetnglClear = reinterpret_cast<nglClearType>(GetProcAddress(lwjgl64dll, "Java_org_lwjgl_opengl_GL11_nglClear"));
		MH_STATUS status = MH_CreateHook(targetnglClear, detournglClear, reinterpret_cast<LPVOID*>(&originalnglClear));
		if (status != MH_OK)
		{
			std::cerr << MH_StatusToString(status) << std::endl;
			return FALSE;
		}
		status = MH_EnableHook(targetnglClear);
		if (status != MH_OK)
		{
			std::cerr << MH_StatusToString(status) << std::endl;
			return FALSE;
		}
	}
	else if (majorVersion == MAJOR_1_16_5) {
		HMODULE lwjgl_opengldll = GetModuleHandleA("lwjgl_opengl.dll");
		if (!lwjgl_opengldll) return FALSE;
		targetglClear = reinterpret_cast<glClearType>(GetProcAddress(lwjgl_opengldll, "Java_org_lwjgl_opengl_GL11C_glClear"));
		MH_STATUS status = MH_CreateHook(targetglClear, detourglClear, reinterpret_cast<LPVOID*>(&originalglClear));
		if (status != MH_OK)
		{
			std::cerr << MH_StatusToString(status) << std::endl;
			return FALSE;
		}
		status = MH_EnableHook(targetglClear);
		if (status != MH_OK)
		{
			std::cerr << MH_StatusToString(status) << std::endl;
			return FALSE;
		}
	}
	if (!JavaClass::init()) return FALSE;
	if (!GUI::init()) return FALSE;
	return TRUE;
}

void Ripterms::clean()
{
	tmp_no_hook = true;
	while (cache) {}
	if (majorVersion == MAJOR_1_8_9) {
		MH_DisableHook(targetnglClear);
		MH_RemoveHook(targetnglClear);
	}
	else if (majorVersion == MAJOR_1_16_5) {
		MH_DisableHook(targetglClear);
		MH_RemoveHook(targetglClear);
	}
	GUI::clean();
	MH_Uninitialize();
	Ripterms::p_env = nullptr;
}

void Ripterms::partialClean()
{
	if (majorVersion == MAJOR_1_8_9) {
		MH_DisableHook(targetnglClear);
		MH_RemoveHook(targetnglClear);
	}
	else if (majorVersion == MAJOR_1_16_5) {
		MH_DisableHook(targetglClear);
		MH_RemoveHook(targetglClear);
	}
	GUI::clean();
	MH_Uninitialize();
	Ripterms::p_env = nullptr;
	delete Ripterms::cache;
	delete Ripterms::classcache;
}
