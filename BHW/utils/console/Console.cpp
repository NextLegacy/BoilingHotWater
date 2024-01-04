#include "BHW/utils/console/Console.hpp"

namespace BHW
{
    void Console::Initialize()
    {
        #ifdef _WIN32

        // TODO: when running the program from the command line, there is no output
        // but dumping into a file works when using Program.exe>file.txt

        // dont create a new console if one already exists
        if (GetConsoleWindow() != NULL) return;

        if (!AllocConsole()) return;

        freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
        freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);
        freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);

        HWND consoleWindow = GetConsoleWindow();

        SetForegroundWindow(consoleWindow);
        SetFocus           (consoleWindow);

        #endif
    }

    void Console::Shutdown()
    {
        #ifdef _WIN32

        fclose(stdout);
        fclose(stderr);
        fclose(stdin);
        FreeConsole();
    
        #endif
    }

    void Console::Write(const std::string& message)
    {
        std::cout << message;
    }

    void Console::WriteLine(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    void Console::Pause()
    {
        std::cin.get();
    }

    std::string Console::ReadLine()
    {
        std::string line;
        std::getline(std::cin, line);

        return line;
    }
}