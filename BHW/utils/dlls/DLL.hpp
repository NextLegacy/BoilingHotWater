#pragma once

#ifdef _WIN32

#include <Windows.h>
#include <string>

namespace BHW
{
    class DLL
    {
    public:
        DLL(const std::string& path = "");

        ~DLL();

        void Load  ();
        void Unload();

        template<typename TFunction>
        TFunction GetFunction(const std::string& name)
        {
            return reinterpret_cast<TFunction>(GetProcAddress(m_handle, name.c_str()));
        }

        inline const std::string& GetPath() const { return m_path; }
        inline void SetPath(const std::string& path) { m_path = path; }

        inline bool IsLoaded() const { return m_handle != nullptr && m_handle != INVALID_HANDLE_VALUE; }

    private:
        std::string m_path  ;
        HMODULE     m_handle;
    };
}

#endif