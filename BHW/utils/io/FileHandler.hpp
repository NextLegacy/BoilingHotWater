#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <comdef.h>
#undef CreateFile
#endif

namespace BHW
{
    std::string ReadFile(const std::string& path);

    void WriteFile(const std::string& path, const std::string& content);

    bool IsFile(const std::string& path);

    bool FileExists(const std::string& path);
    bool PathExists(const std::string& path);

    std::string FileName(const std::string& path);
    std::string FileNameWithoutExtension(const std::string& path);

    std::string GetFileDirectory(const std::string& path);

    void CreateFolder(const std::string& path);
    void CreateFile(const std::string& path);

    std::string SelectFolder(const std::string& title, const std::string& defaultPath, HWND parent);

    std::vector<std::string> GetFilesInFolder(const std::string& path, const std::string& extension);

    std::string GetCurrentPath();
    std::string GetExecutablePath();

    std::string GetAbsolutePath(const std::string& path);
    bool IsAbsolutePath(const std::string& path);

    bool FileExtensionIs(const std::string& path, const std::string& extension);

    std::string CombinePaths(const std::string& path1, const std::string& path2);
}