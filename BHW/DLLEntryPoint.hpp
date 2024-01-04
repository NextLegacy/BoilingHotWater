#pragma once

#ifdef _WIN32

#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

#endif

namespace BHW
{
    extern int ProcessAttach();
    extern int ProcessDetach();

    extern int ThreadAttach ();
    extern int ThreadDetach ();
}