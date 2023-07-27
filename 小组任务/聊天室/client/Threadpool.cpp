#include "public.hpp"
// 任务队列
template <typename T>
void TaskQueue<T>::addTask(T &t)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.emplace(t);
}
template <typename T>
bool TaskQueue<T>::takeTask(T &t)
{
    std::unique_lock<std::mutex> lock(m_mutex); // 队列加锁

    if (m_queue.empty())
        return false;
    t = std::move(m_queue.front()); // 取出队首元素，返回队首元素值，将值转移到t上
    m_queue.pop();                  // 弹出入队的第一个元素
    return true;
}
template <typename T>
bool TaskQueue<T>::empty() // 返回队列是否为空
{
    std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变

    return m_queue.empty();
}

// 线程池
ThreadPool::ThreadPool(int minNum, int maxNum)
{
    for (int i = 0; i < minNum; ++i)
    {
        m_threadsID.emplace_back(worker);
    }
    std::thread t(manager); // 创建管理者线程, 1个
}
//添加任务
template <typename F, typename... Args>
auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
{
    // Create a function with bounded parameter ready to execute
    std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...); // 连接函数和参数定义，特殊函数类型，避免左右值错误

    // Encapsulate it into a shared pointer in order to be able to copy construct
    auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

    // Warp packaged task into void function
    std::function<void()> warpper_func = [task_ptr]()
    {
        (*task_ptr)();
    };

    // 队列通用安全封包函数，并压入安全队列
    m_queue.addTask(warpper_func);

    // 唤醒一个等待中的线程
    m_conditional_lock.notify_one();

    // 返回先前注册的任务指针
    return task_ptr->get_future();
}
int ThreadPool::getAliveNumber()
{
    int threadNum = 0;
    m_conditional_mutex.lock();
    threadNum = m_aliveNum;
    m_conditional_mutex.unlock();
    return threadNum;
}
int ThreadPool::getBusyNumber()
{
    int busyNum = 0;
    m_conditional_mutex.lock();
    busyNum = m_busyNum;
    m_conditional_mutex.unlock();
    return busyNum;
}
void* ThreadPool::worker()
{
    // 一直不停的工作
    while (true)
    {
        // 访问任务队列(共享资源)加锁
        m_conditional_mutex.lock();
        // 判断任务队列是否为空, 如果为空工作线程阻塞
        while (this->m_taskQ.empty() && !this->m_shutdown)
        {
            cout << "thread " << to_string(pthread_self()) << " waiting..." << endl;
            // 阻塞线程
            std::unique_lock<std::mutex> lock(this->m_conditional_mutex);
            this->m_conditional_lock.wait(lock);
            // 解除阻塞之后, 判断是否要销毁线程
            if (this->m_exitNum > 0)
            {
                this->m_exitNum--;
                if (this->m_aliveNum > this->m_minNum)
                {
                    this->m_aliveNum--;
                    m_conditional_mutex.unlock();
                    this->threadExit();
                }
            }
        }
        // 判断线程池是否被关闭了
        if (this->m_shutdown)
        {
            m_conditional_mutex.unlock();
            this->threadExit();
        }

        // 从任务队列中取出一个任务
        std::function<void()> func;
        bool dequeued= this->m_taskQ.takeTask(func);
        // 工作的线程+1
        this->m_busyNum++;
        // 线程池解锁
        m_conditional_mutex.unlock();
        // 执行任务
        cout << "thread " << to_string(pthread_self()) << " start working..." << endl;
        if (dequeued)
            func();
        // 任务处理结束
        cout << "thread " << to_string(pthread_self()) << " end working...";
        m_conditional_mutex.lock();
        this->m_busyNum--;
        m_conditional_mutex.unlock();
    }

    return nullptr;
}
void ThreadPool::threadExit()
{
    std::thread::id tid = std::this_thread::get_id();
    for (int i = 0; i < m_maxNum; ++i)
    {
        if (m_threadsID[i].get_id() == tid)
        {
            cout << "threadExit() function: thread " 
                << to_string(pthread_self()) << " exiting..." << endl;
            m_threadsID[i];
            break;
        }
    }
    pthread_exit(NULL);
}