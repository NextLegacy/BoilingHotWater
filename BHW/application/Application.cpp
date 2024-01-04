#include "BHW/application/Application.hpp"

namespace BHW
{
    Application::Application() : m_isRunning(false) { }

    void Application::Run()
    {   
        m_isRunning = true;

        ApplicationEntryPoint();

        m_isRunning = false;
    }

    void Application::Stop()
    {
        m_isRunning = false;
    }
}