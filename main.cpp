#include "mbed.h"

Mutex mutex;

Thread thread_first;
Thread thread_second;
Thread thread_third;

void high_priority_task() {
    printf("Entered in high priority task, thread: %d\r\n", osThreadGetId());
    mutex.lock();
    printf("Doing some work, thread: %d\r\n", osThreadGetId());
    ThisThread::sleep_for(500);
    printf("Finished work, thread: %d\r\n", osThreadGetId());
    mutex.unlock();
    printf("Exit in high priority task, thread: %d\r\n", osThreadGetId());
}

void normal_priority_task() {
    printf("Entered in normal priority task, thread: %d\r\n", osThreadGetId());
    ThisThread::sleep_for(100);
    printf("Exit in normal priority task, thread: %d\r\n", osThreadGetId());
}

// main() runs in its own thread in the OS
int main()
{
    printf("Starting program...\r\n");

    thread_first.start(high_priority_task);
    thread_first.set_priority(osPriorityLow);
    
    ThisThread::sleep_for(100);

    thread_third.start(high_priority_task);
    thread_third.set_priority(osPriorityHigh);

    thread_second.start(normal_priority_task);
    thread_second.set_priority(osPriorityNormal);

    thread_first.join();
    thread_second.join();
    thread_third.join();
}

