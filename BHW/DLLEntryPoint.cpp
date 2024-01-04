#include "DLLEntryPoint.hpp"

#ifdef _WIN32

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH: return BHW::ProcessAttach();
    case DLL_PROCESS_DETACH: return BHW::ProcessDetach();
    case DLL_THREAD_ATTACH : return BHW::ThreadAttach ();
    case DLL_THREAD_DETACH : return BHW::ThreadDetach ();
    default                : return FALSE               ;
    }
}

#endif // _WIN32