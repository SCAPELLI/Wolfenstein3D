#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
    std::thread myThread;

public:
    Thread() = default;
    virtual ~Thread() = default;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    virtual void run() = 0;
    void start();
    void join();
    Thread(Thread&& other) noexcept;
    Thread& operator=(Thread&& other) noexcept;
};

#endif
