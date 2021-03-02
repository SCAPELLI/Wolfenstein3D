#include <algorithm>
#include <thread>
#include "../include/Thread.h"

void Thread::start() {
    myThread = std::thread(&Thread::run, this);
}
bool Thread::joinable() {
    return myThread.joinable();
}
void Thread::join() {
    myThread.join();
}
Thread::Thread(Thread&& other) noexcept {
    myThread = std::move(other.myThread);
}
Thread& Thread::operator=(Thread&& other) noexcept {
    myThread = std::move(other.myThread);
    return *this;
}
