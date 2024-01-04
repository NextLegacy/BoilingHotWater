#include "BHW/utils/logger/LoggerLevel.hpp"

namespace BHW
{
    LoggerLevel::LoggerLevel(LevelFunction levelFunction, MessageFunction messageFunction) 
        : m_levelFunction(levelFunction), m_messageFunction(messageFunction) { }

    LoggerLevel LoggerLevel::DEFAULT = LoggerLevel
    (
        []()                    { return c_DEFAULT(""); },
        [](std::string message) { return c_DEFAULT(message); }
    );

    LoggerLevel LoggerLevel::INFO = LoggerLevel
    (
        []()                    { return c_INFO("[INFO]"); },
        [](std::string message) { return c_INFO(message ); }
    );

    LoggerLevel LoggerLevel::WARN = LoggerLevel
    (
        []()                    { return c_WARN("[WARN]"); },
        [](std::string message) { return c_WARN(message ); }
    );

    LoggerLevel LoggerLevel::ERROR_ = LoggerLevel
    (
        []()                    { return c_ERROR_("[ERROR_]"); },
        [](std::string message) { return c_ERROR_(message  ); }
    );

    LoggerLevel LoggerLevel::TIME = LoggerLevel
    (
        []()                    { return c_TIME("[" + std::format("{:%H:%M:%S}", std::chrono::system_clock::now()) + "]"); },
        [](std::string message) { return message; }
    );

    //LoggerLevel BHW::CALLER = LoggerLevel
    //(
    //    []()                    { return c_CALLER("[CALLER]"); },
    //    [](std::string message) { return message; }
    //);

    LoggerLevel LoggerLevel::DEBUG = LoggerLevel
    (
        []()                    { return c_DEBUG("[DEBUG]"); },
        [](std::string message) { return c_DEBUG(message  ); }
    );

    namespace
    {
        ANSICode c_DEFAULT = ANSICodeBuilder().Build();
        
        ANSICode c_INFO = ANSICodeBuilder()
            .Foreground(0x42abff)
        .Build();

        ANSICode c_WARN = ANSICodeBuilder()
            .Foreground(0xffff42)
        .Build();

        ANSICode c_ERROR_ = ANSICodeBuilder()
            .Foreground(0xff4242)
        .Build();

        ANSICode c_TIME = ANSICodeBuilder()
            .Foreground(0x42ff42)
        .Build();

        //ANSICode c_CALLER = ANSICodeBuilder()
        //    .Foreground(0xff42ff)
        //.Build();

        ANSICode c_DEBUG = ANSICodeBuilder()
            .Foreground(0x01ab42)
        .Build();        
    }
}