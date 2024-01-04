#include "BHW/EntryPoint.hpp"

#ifdef _WIN32

#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    std::vector<std::string> args;

    // I've did not put any thought into this.
    // for some tests I've made, it seems to work.
    // should be fine for now.

    // creates a std::vector<std::string> containing the command line arguments

    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    for (int i = 0; i < argc; i++)
    {
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, argv[i], (int)wcslen(argv[i]), NULL, 0, NULL, NULL);
        std::string arg(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, argv[i], (int)wcslen(argv[i]), &arg[0], size_needed, NULL, NULL);
        args.push_back(arg);
    }

    return BHW::EntryPoint(args);
}

#endif // _WIN32

int main(const int argc, const char** argv)
{
    std::vector<std::string> args;

    for (int i = 0; i < argc; i++) 
        args.push_back(argv[i]);
    
    return BHW::EntryPoint(args);
}


