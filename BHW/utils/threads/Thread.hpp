#pragma once

#include <thread>

#include <functional>

namespace BHW
{
    class Thread
    {
    public:
        Thread(std::function<void(Thread&)> function);
        
        ~Thread();

        void Activate  ();

        void Deactivate();

        void ForceStop ();

        void Join      ();

        inline bool IsRunning () const { return m_isRunning ; }
        inline bool ShouldStop() const { return m_shouldStop || !m_isRunning; }

    private:
        void Run();

    private:
        std::thread* m_thread;

        bool m_shouldStop;
        bool m_isRunning ;

        std::function<void(Thread&)> m_function;
    };
}