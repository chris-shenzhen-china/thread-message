#pragma once


#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>


class CTimer
{
private:
    std::atomic<bool> m_expired;
    std::atomic<bool> m_tryToExpire;
    std::mutex m_mutex;
    std::condition_variable m_condition;


public:
    CTimer() :m_expired(true), m_tryToExpire(false)
    {
    }

    CTimer(const CTimer& t)
    {
        m_expired = t.m_expired.load();
        m_tryToExpire = t.m_tryToExpire.load();
    }

    ~CTimer()
    {
        expire();
        //std::cout << "timer destructed!" << std::endl;
    }

    void startTimer(int interval, std::function<void()> task)
    {
        if (m_expired == false)
        {
            //std::cout << "timer is currently running, please expire it first..." << std::endl;
            return;
        }

        m_expired = false;
        std::thread([this, interval, task]()
        {
            while (!m_tryToExpire)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                task();
            }

            //std::cout << "stop task..." << std::endl;
            {
                std::lock_guard<std::mutex> locker(m_mutex);
                m_expired = true;
                m_condition.notify_one();
            }
        }).detach();
    }

    //停止定时器
    void expire()
    {
        if (m_expired)
        {
            return;
        }

        if (m_tryToExpire)
        {
            //std::cout << "timer is trying to expire, please wait..." << std::endl;
            return;
        }

        m_tryToExpire = true;
        {
            std::unique_lock<std::mutex> locker(m_mutex);
            m_condition.wait(locker, [this] {return m_expired == true; });
            if (m_expired == true)
            {
                //              std::cout << "timer expired!" << std::endl;
                m_tryToExpire = false;
            }
        }
    }

    template<typename callable, class... arguments>
    void syncWait(int after, callable&& f, arguments&&... args)
    {

        std::function<typename std::result_of<callable(arguments...)>::type()> task
        (std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
        std::this_thread::sleep_for(std::chrono::milliseconds(after));
        task();
    }

    template<typename callable, class... arguments>
    void asyncWait(int after, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task
        (std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        std::thread([after, task]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }).detach();
    }

};
