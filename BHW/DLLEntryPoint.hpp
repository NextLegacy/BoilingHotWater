#pragma once

namespace BHW
{
    extern int ProcessAttach();
    extern int ProcessDetach();

    extern int ThreadAttach ();
    extern int ThreadDetach ();
}

#ifdef _WIN32

#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

#endif