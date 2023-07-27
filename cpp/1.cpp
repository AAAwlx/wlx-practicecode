#include <iostream>
#include <thread>
#include <vector>

// 定义线程执行体函数
void threadFunction(int threadId)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread " << threadId << " executing... Count: " << i << std::endl;
    }
}

int main()
{
    const int numThreads = 5;
    std::vector<std::thread> threads; // 存放线程对象的容器

    // 循环创建多个线程
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(threadFunction, i); // 创建线程并将线程执行体函数和参数传递给它
    }

    // 等待所有线程执行完毕
    for (auto &thread : threads)
    {
        thread.join();
    }

    std::cout << "All threads have finished executing." << std::endl;

    return 0;
}

