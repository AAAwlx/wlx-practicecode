#include <iostream>
#include <thread>
#include <atomic>
#include<unistd.h>
std::atomic<bool> stopFlag(false);

// 子线程函数
void threadFunction()
{
    while (!stopFlag)
    {
        // 子线程的工作逻辑
       std::cout << "子线程执行中..." << std::endl;
       sleep(1);
    }
}

int main()
{
    // 创建并启动子线程
    std::thread myThread(threadFunction);
    sleep(2);
    std::cout << "停止子线程..." << std::endl;
    stopFlag = true;

    // 等待子线程结束
    if (myThread.joinable())
        myThread.join();

    return 0;
}

