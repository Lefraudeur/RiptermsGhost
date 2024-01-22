#include <Windows.h>
#include <iostream>
#include "Ripterms/Ripterms.h"

#define RIPTERMS_INJECTOR 66666

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case RIPTERMS_INJECTOR:
    case DLL_PROCESS_ATTACH:
    {
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.

        if (!Ripterms::init(hinstDLL))
        {
            std::cin.ignore();
            FreeConsole();
            return FALSE;
        }
        std::cout << "Init success" << std::endl;
        return TRUE;
    }

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        if (lpvReserved != nullptr)
        {
            //process termination
            Ripterms::partialClean();
            break;
        }
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}