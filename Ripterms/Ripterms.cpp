#include "Ripterms.h"
#include <Windows.h>
#include <psapi.h>
#include <iostream>

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
		char str[32];
		GetWindowTextA(hwnd, str, 32);
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

Ripterms::JavaClass::JavaClass(const std::string& class_path)
{
	fill(class_path);
	this->class_paths.push_back(class_path);
}

Ripterms::JavaClass::JavaClass()
{
}

Ripterms::JavaClass::JavaClass(JavaClass& otherJavaClass)
{
	if (otherJavaClass.javaClass) this->javaClass = (jclass)p_env->NewLocalRef(otherJavaClass.javaClass);
	this->class_paths = otherJavaClass.class_paths;
	this->fields = otherJavaClass.fields;
	this->methods = otherJavaClass.methods;
}

Ripterms::JavaClass::~JavaClass()
{
	if (javaClass) p_env->DeleteLocalRef(javaClass);
}

bool Ripterms::JavaClass::isFilled(const std::string& class_path)
{
	for (const std::string& str : class_paths) {
		if (str == class_path) return true;
	}
	return false;
}

void Ripterms::JavaClass::fill(const std::string& class_path)
{
	if (this->mappings.empty()) {
		std::string windowName = getCurrentWindowName();
		size_t ignore = windowName.find(" (v");
		if (windowName.substr(0, ignore) == "Lunar Client 1.8.9") {

		}
	}
}

void Ripterms::init()
{

}