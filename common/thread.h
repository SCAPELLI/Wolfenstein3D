#ifndef _THREAD_H
#define _THREAD_H

#include <thread>


class Thread{
private:
    std::thread thread;
public:
    Thread();
    virtual ~Thread();
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
    void start();
    void join();
    virtual void run() = 0;
};

#endif
