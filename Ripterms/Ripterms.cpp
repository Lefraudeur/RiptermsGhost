#include "Ripterms.h"
#include <psapi.h>
#include <iostream>
#include "Cache/Cache.h"
#include "GUI/GUI.h"

void mainLoop()
{
	static Ripterms::Timer timer(std::chrono::milliseconds(2));
	if (!timer.isElapsed()) return;
	if (!Ripterms::Cache::fillCache()) return;
}

typedef void(*nglClearType)(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer);

nglClearType originalnglClear = nullptr;

bool tmp_no_hook = false;

void detournglClear(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer)
{
	static bool runMainLoop = false;

	if (tmp_no_hook) return originalnglClear(env, clazz, mask, function_pointer);

	Ripterms::p_env = env;

	static bool runonce = true;
	if (runonce)
	{
		env->GetJavaVM(&Ripterms::p_jvm);
		Ripterms::p_jvm->GetEnv((void**)&Ripterms::p_tienv, JVMTI_VERSION);
		runMainLoop = Ripterms::JavaClass::fillAll();
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
	if (windowName.find("Lunar Client 1.8.9") != std::string::npos) version = LUNAR_1_8_9;
	if (version == UNDEFINED) {
		std::cerr << "unknown version" << std::endl;
		return FALSE;
	}
	MH_Initialize();
	HMODULE lwjgl64dll = GetModuleHandleA("lwjgl64.dll");
	if (!lwjgl64dll) return FALSE;
	FARPROC targetnglClear = GetProcAddress(lwjgl64dll, "Java_org_lwjgl_opengl_GL11_nglClear");
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
	if (!GUI::init()) return FALSE;
	return TRUE;
}

void Ripterms::clean()
{
	tmp_no_hook = true;
	MH_DisableHook(MH_ALL_HOOKS);
	GUI::clean();
	MH_Uninitialize();
	if (p_tienv) p_tienv->DisposeEnvironment();
	p_env = nullptr;
}
