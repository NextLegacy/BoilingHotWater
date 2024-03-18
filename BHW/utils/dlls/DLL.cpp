#include "BHW/utils/dlls/DLL.hpp"

#include "BHW/utils/console/Console.hpp"

namespace BHW
{
    DLL::DLL(const std::string& path) : m_path(path), m_handle(nullptr)
    {
    }

    DLL::~DLL()
    {
        Unload();
    }

    void DLL::Load()
    {
        //BHW::Console::WriteLine("Loading DLL: " + m_path);

        if (m_handle) return;

        m_handle = LoadLibraryA(m_path.c_str());
    }

    void DLL::Unload()
    {
        if (!m_handle)
            return;

        FreeLibrary(m_handle);
        m_handle = nullptr;
    }
}