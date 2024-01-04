#pragma once

#define BHW_DLL_EXPORT __declspec(dllexport)
#define BHW_DLL_IMPORT __declspec(dllimport)

#include <Windows.h>

namespace BHW
{
    class DLL
    {
    public:
        DLL(const char* path)
        {
            m_handle = LoadLibraryA(path);
        }

        ~DLL()
        {
            FreeLibrary(m_handle);
        }

        template<typename TFunction>
        TFunction GetFunction(const char* name)
        {
            return reinterpret_cast<TFunction>(GetProcAddress(m_handle, name));
        }

    private:
        HMODULE m_handle;
    };
}