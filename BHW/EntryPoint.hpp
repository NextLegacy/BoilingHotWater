#pragma once

#include <vector> 
#include <string>

namespace BHW
{
    extern int EntryPoint(std::vector<std::string> args);
}

#ifdef _WIN32

#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

#else // if not _WIN32

int main(const int argc, const char** argv);

#endif // _WIN32
