#include <Windows.h>
#include <iostream>
#include "Ripterms/Ripterms.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    static FILE* fbuffer1 = nullptr, * fbuffer2 = nullptr, *fbuffer3 = nullptr;
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        AllocConsole();
        freopen_s(&fbuffer1, "CONOUT$", "w", stdout);
        freopen_s(&fbuffer2, "CONOUT$", "w", stderr);
        freopen_s(&fbuffer3, "CONIN$", "r", stdin);
        Ripterms::module = hinstDLL;
        if (Ripterms::init() == FALSE) {
            std::cin.ignore();
            Ripterms::clean();
            fclose(fbuffer1);
            fclose(fbuffer2);
            fclose(fbuffer3);
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
        if (lpvReserved != nullptr) {
            //process termination
            Ripterms::partialClean();
            fclose(fbuffer1);
            fclose(fbuffer2);
            fclose(fbuffer3);
            FreeConsole();
            break;
        }
        Ripterms::clean();
        fclose(fbuffer1);
        fclose(fbuffer2);
        fclose(fbuffer3);
        FreeConsole();
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}