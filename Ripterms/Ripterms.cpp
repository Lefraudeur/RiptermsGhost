#include "Ripterms.h"
#include <iostream>
#include "Cache/Cache.h"
#include "GUI/GUI.h"
#include "Modules/Modules.h"
#include "JavaClass/JavaClass.h"
#include "Patcher/Patcher.h"
#include "../java/lang/System/System.h"
#include "Event/Event.h"
#include "Hook/Hook.h"

static void mainLoop()
{
	static Ripterms::CTimer timer = std::chrono::milliseconds(5);
	if (!timer.isElapsed() || !Ripterms::cache->fillCache()) return;
	Ripterms::Modules::runAll();
}

namespace
{
	typedef void(JNICALL* nglClearType)(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer);
	nglClearType originalnglClear = nullptr;
	nglClearType targetnglClear = nullptr;

	typedef void(JNICALL* glClearType)(JNIEnv* env, jclass clazz, jint mask);
	glClearType originalglClear = nullptr;
	glClearType targetglClear = nullptr;

	Ripterms::Hook* hook = nullptr;

	bool runMainLoop = false;

	FILE* console_buffer1 = nullptr, * console_buffer2 = nullptr, * console_buffer3 = nullptr;
}

static void JNICALL detournglClear(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer)
{
	static bool runonce = true;
	Ripterms::Event event(env, mask);
	if (event.isEvent())
	{
		if (!runonce && runMainLoop) event.dispatch();
		return;
	}

	if (runonce)
	{
		Ripterms::p_env = env;
		env->GetJavaVM(&Ripterms::p_jvm);
		Ripterms::p_jvm->GetEnv((void**)&Ripterms::p_tienv, JVMTI_VERSION_1_2);
		runMainLoop = Ripterms::JavaClassV2::init();
		if (runMainLoop) runMainLoop = Ripterms::Patcher::init();
		runonce = false;
	}

	if (GetAsyncKeyState(VK_END))
	{
		Ripterms::clean();
		return targetnglClear(env, clazz, mask, function_pointer);
	}
	if (runMainLoop) mainLoop();
	return originalnglClear(env, clazz, mask, function_pointer);
}

static void JNICALL detourglClear(JNIEnv* env, jclass clazz, jint mask)
{
	static bool runonce = true;
	Ripterms::Event event(env, mask);
	if (event.isEvent())
	{
		if (!runonce && runMainLoop) event.dispatch();
		return;
	}

	if (runonce)
	{
		Ripterms::p_env = env;
		env->GetJavaVM(&Ripterms::p_jvm);
		Ripterms::p_jvm->GetEnv((void**)&Ripterms::p_tienv, JVMTI_VERSION_1_2);
		runMainLoop = Ripterms::JavaClassV2::init();
		if (runMainLoop) runMainLoop = Ripterms::Patcher::init();
		runonce = false;
	}

	if (GetAsyncKeyState(VK_END))
	{
		Ripterms::clean();
		return targetglClear(env, clazz, mask);
	}
	if (runMainLoop) mainLoop();
	return originalglClear(env, clazz, mask);
}

struct Process
{
	DWORD pid;
	HWND window;
};

static BOOL CALLBACK EnumWindowsCallback(_In_ HWND hwnd, _In_ LPARAM lParam)
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

HWND Ripterms::getCurrentWindow()
{
	HANDLE current = GetCurrentProcess();
	Process process = { GetProcessId(current) };
	CloseHandle(current);
	EnumWindows(&EnumWindowsCallback, (LPARAM)&process);
	return process.window;
}

static std::string getWindowName(HWND hwnd)
{
	char str[64];
	GetWindowTextA(hwnd, str, 64);
	return std::string(str);
}


BOOL Ripterms::init(HMODULE dll)
{
	Ripterms::module = dll;
	AllocConsole();
	freopen_s(&console_buffer1, "CONOUT$", "w", stdout);
	freopen_s(&console_buffer2, "CONOUT$", "w", stderr);
	freopen_s(&console_buffer3, "CONIN$", "r", stdin);
	Ripterms::window = getCurrentWindow();
	std::string windowName = getWindowName(window);
	if (windowName.find("Lunar Client 1.8.9") != std::string::npos)
	{
		version = LUNAR_1_8_9;
		majorVersion = MAJOR_1_8_9;
	}
	else if 
	(
		(windowName.find("Badlion Minecraft Client") != std::string::npos && windowName.find("1.8.9") != std::string::npos)
	)
	{
		version = VANILLA_1_8_9;
		majorVersion = MAJOR_1_8_9;
	}
	else if (windowName.find("Lunar Client 1.7.10") != std::string::npos)
	{
		version = LUNAR_1_7_10;
		majorVersion = MAJOR_1_8_9;
	}
	else if 
	(
		windowName.find("Lunar Client 1.16.5") != std::string::npos ||
		windowName.find("Lunar Client 1.17.1") != std::string::npos ||
		windowName.find("Lunar Client 1.18.2") != std::string::npos
	)
	{
		version = LUNAR_1_16_5;
		majorVersion = MAJOR_1_16_5;
	}
	else if (windowName.find("Paladium") != std::string::npos || windowName.find("Minecraft 1.7.10") != std::string::npos)
	{
		version = FORGE_1_7_10;
		majorVersion = MAJOR_1_8_9;
	}
	else
	{
		std::cerr << "unknown version" << std::endl;
		return FALSE;
	}
	if (majorVersion == MAJOR_1_8_9)
	{
		Ripterms::Module lwjgl("lwjgl64.dll");
		if (!lwjgl)
			return FALSE;
		targetnglClear = (nglClearType)lwjgl.getProcAddress("Java_org_lwjgl_opengl_GL11_nglClear");
		hook = new Ripterms::Hook(6, targetnglClear, detournglClear, (void**)&originalnglClear, Ripterms::Hook::RELATIVE_5B_JMP);
	}
	else if (majorVersion == MAJOR_1_16_5)
	{
		Ripterms::Module lwjgl("lwjgl_opengl.dll");
		if (!lwjgl)
			return FALSE;
		targetglClear = (glClearType)lwjgl.getProcAddress("Java_org_lwjgl_opengl_GL11C_glClear");
		hook = new Ripterms::Hook(17, targetglClear, detourglClear, (void**)&originalglClear, Ripterms::Hook::RELATIVE_5B_JMP);
	}
	if (!GUI::init()) return FALSE;
	return TRUE;
}

void Ripterms::clean()
{
	Ripterms::Modules::cleanAll();
	Ripterms::Patcher::clean();
	delete Ripterms::cache;
	System::gc();
	Ripterms::JavaClassV2::clean();
	if (Ripterms::p_tienv)
		Ripterms::p_tienv->DisposeEnvironment();
	GUI::clean();
	fclose(console_buffer1);
	fclose(console_buffer2);
	fclose(console_buffer3);
	FreeConsole();
	delete hook;
	std::thread a(FreeLibrary, Ripterms::module);
	a.detach();
}

void Ripterms::partialClean()
{
	Ripterms::p_env = nullptr;
	Ripterms::Modules::cleanAll();
	Ripterms::JavaClassV2::clean();
	delete Ripterms::cache;
}
