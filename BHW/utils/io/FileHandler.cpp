#include "BHW/utils/io/FileHandler.hpp"

#include <fstream>
#include <filesystem>
#include "BHW/utils/Debug.hpp"

namespace BHW
{
    std::string ReadFile(const std::string& path)
    {
        std::ifstream file(path);

        std::string result;

        std::string line;

        while (std::getline(file, line))
        {
            result += line + "\n";
        }

        file.close();

        return result;
    }

    void WriteFile(const std::string& path, const std::string& content)
    {
        std::ofstream file(path);

        file << content;

        file.close();
    }

    bool IsFile(const std::string& path)
    {
        return std::filesystem::is_regular_file(std::filesystem::path(path));
    }

    bool FileExists(const std::string& path)
    {
        std::ifstream file(path);

        bool result = file.good();

        file.close();

        return result;
    }

    bool PathExists(const std::string& path)
    {
        return std::filesystem::exists(path);
    }

    std::string FileName(const std::string& path)
    {
        return std::filesystem::path(path).filename().string();
    }

    std::string FileNameWithoutExtension(const std::string& path)
    {
        return std::filesystem::path(path).stem().string();
    }

    std::string GetFileDirectory(const std::string& path)
    {
        return std::filesystem::path(path).parent_path().string();
    }

    void CreateFolder(const std::string& path)
    {
        std::filesystem::create_directories(path);
    }

    void CreateFile(const std::string& path)
    {
        std::ofstream file(path);
        file.close();
    }

    std::string SelectFolder(const std::string& title, const std::string& defaultPath, HWND parent)
    {
#ifdef _WIN32

        std::string folderPath;
        IFileOpenDialog* pfd;

        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pfd));
            if (SUCCEEDED(hr))
            {
                DWORD dwOptions;
                if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
                {
                    pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
                }

                hr = pfd->Show(parent);
                if (SUCCEEDED(hr))
                {
                    IShellItem* psi;
                    hr = pfd->GetResult(&psi);
                    if (SUCCEEDED(hr))
                    {
                        PWSTR pszPath;
                        hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
                        if (SUCCEEDED(hr))
                        {
                            int size_needed = WideCharToMultiByte(CP_UTF8, 0, pszPath, -1, NULL, 0, NULL, NULL);
                            folderPath.resize(size_needed);
                            WideCharToMultiByte(CP_UTF8, 0, pszPath, -1, &folderPath[0], size_needed, NULL, NULL);
                            CoTaskMemFree(pszPath);
                        }
                        psi->Release();
                    }
                }
                pfd->Release();
            }
            CoUninitialize();
        }

        return std::string(folderPath.begin(), folderPath.end());
#else
        return "";
#endif
    }

    std::vector<std::string> GetFilesInFolder(const std::string& path, const std::string& extension)
    {
        if (!std::filesystem::exists(path)) return std::vector<std::string>();

        std::vector<std::string> files;

        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if(entry.path().extension() == extension || entry.path().filename() == extension || extension == "*")
            {
                files.push_back(entry.path().string());
            }
        }

        return files;
    }
    
    std::string GetCurrentPath()
    {
        return std::filesystem::current_path().string();
    }

    std::string GetExecutablePath()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, sizeof(buffer));
        return std::filesystem::path(buffer).parent_path().string();
    }

    std::string GetAbsolutePath(const std::string& path)
    {
        return std::filesystem::absolute(path).string();
    }

    bool IsAbsolutePath(const std::string& path)
    {
        return std::filesystem::path(path).is_absolute();
    }

    bool FileExtensionIs(const std::string& path, const std::string& extension)
    {
        return std::filesystem::path(path).extension() == extension || std::filesystem::path(path).filename() == extension;
    }

    std::string CombinePaths(const std::string& path1, const std::string& path2)
    {
        return (std::filesystem::path(path1) / std::filesystem::path(path2)).string();
    }
}