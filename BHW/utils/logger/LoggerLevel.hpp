#pragma once

#include <functional>
#include <map>

#include <chrono>
#include <string>
#include <format>

#include "BHW/utils/console/ANSI.hpp"

namespace BHW
{
    struct LoggerLevel
    {
    friend class Logger;

    typedef std::function<std::string()>            LevelFunction  ;
    typedef std::function<std::string(std::string)> MessageFunction;

    public:
        LoggerLevel(LevelFunction levelFunction, MessageFunction messageFunction);

    public:
        static LoggerLevel DEFAULT;

        static LoggerLevel INFO  ;
        static LoggerLevel WARN  ;
        static LoggerLevel ERROR_;
        static LoggerLevel TIME  ;
        //static LoggerLevel CALLER;
        static LoggerLevel DEBUG ;

    private:
        LevelFunction   m_levelFunction;
        MessageFunction m_messageFunction;
    };

    namespace 
    {
        extern ANSICode c_DEFAULT;
        extern ANSICode c_INFO   ;
        extern ANSICode c_WARN   ;
        extern ANSICode c_ERROR_ ;
        extern ANSICode c_TIME   ;
        //extern ANSICode c_CALLER ;
        extern ANSICode c_DEBUG  ;
    }
}