#include "BHW/utils/logger/Logger.hpp"

namespace BHW
{
    Logger::Logger() : DynamicEventSystem<LoggerBaseEvent>() { }

    void Logger::Log(std::string message, std::vector<LoggerLevel> levels)
    {
        std::string levelString = "";

        for (LoggerLevel level : levels)
        {
            levelString += level.m_levelFunction() + " ";
        }

        LoggedMessage logMessage = LoggedMessage
        (
            std::chrono::system_clock::now(),
            levelString,
            (levels.empty() ? LoggerLevel::DEFAULT : levels.back()).m_messageFunction(message)
        );
    
        Log(logMessage);
    }

    void Logger::Log(LoggedMessage message)
    {
        m_messages.push_back(message);
        
        //ForEachEventSystem(&LoggerBaseEvent::OnLog, message);
    }

    void Logger::DumpAll()
    {
        for (LoggedMessage message : m_messages)
        {
            //ForEachEventSystem(&LoggerBaseEvent::OnLog, message);
        }
    }

    void Logger::Clear()
    {
        m_messages.clear();
    }
}