#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
//#include <comdef.h>
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

    #ifdef _WIN32
    std::string SelectFolder(const std::string& title, const std::string& defaultPath, HWND parent);
    #endif

    std::vector<std::string> GetFilesInFolder(const std::string& path, const std::string& extension);

#ifdef _WIN32
    std::string GetCurrentPath();
    std::string GetExecutablePath();
#endif

    std::string GetAbsolutePath(const std::string& path);
    bool IsAbsolutePath(const std::string& path);

    bool FileExtensionIs(const std::string& path, const std::string& extension);

    template<typename ...Paths>
    std::string CombinePaths(const std::string& path, Paths... paths)
    {
        std::string result = path;

        std::vector<std::string> pathsVector = { paths... };

        for (const std::string& path : pathsVector)
        {
            result += "\\" + path;
        }

        return result;
    }

    std::string GetRelativePath(const std::string& path, const std::string& relativeTo);
}