#include "BHW/utils/threads/Thread.hpp"

#include "BHW/utils/Time.hpp"

namespace BHW
{
    Thread::Thread(std::function<void(Thread&)> function)
        : m_function  (function), 
          m_isRunning (false   ), 
          m_shouldStop(false   ),
          m_thread    (nullptr ) { }

    Thread::~Thread()
    {
        Deactivate();
    }

    void Thread::Activate()
    {
        if (m_isRunning) Deactivate();

        m_isRunning  = true ;
        m_shouldStop = false;
        
        m_thread = new std::thread(&Thread::Run, this);
    }

    void Thread::Deactivate()
    {
        if (!m_isRunning || m_shouldStop) return;

        Join();

        m_isRunning  = false;
        m_shouldStop = true ;

        //delete &m_thread;

        m_shouldStop = false;
    }

    void Thread::ForceStop()
    {
        if (!m_isRunning) return;

        m_isRunning  = false;
        m_shouldStop = true ;

        m_thread->detach();

        //delete &m_thread;

        m_shouldStop = false;
    }

    void Thread::Join()
    {
        if (!m_isRunning) return;
        
        m_thread->join();
    }

    void Thread::Run()
    {
        m_isRunning  = true ;
        m_shouldStop = false;

        m_function(*this);

        m_isRunning  = false;
        m_shouldStop = false;
    }
}