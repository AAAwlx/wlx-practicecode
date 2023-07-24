#include <unistd.h>

#include <mutex>
#include <queue>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>
#include <iostream>
#include <random>
// Thread safe implementation of a Queue using a std::queue
template <typename T>
class SafeQueue
{
private:
    std::queue<T> m_queue; //利用模板函数构造队列

    std::mutex m_mutex; // 访问互斥信号量

public:
    SafeQueue() {}
    SafeQueue(SafeQueue &&other) {}
    ~SafeQueue() {}

    bool empty() // 返回队列是否为空
    {
        std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变

        return m_queue.empty();
    }

    int size()
    {
        std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变

        return m_queue.size();
    }

    // 队列添加元素
    void enqueue(T &t)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.emplace(t);
    }

    // 队列取出元素
    bool dequeue(T &t)
    {
        std::unique_lock<std::mutex> lock(m_mutex); // 队列加锁

        if (m_queue.empty())
            return false;
        t = std::move(m_queue.front()); // 取出队首元素，返回队首元素值，并进行右值引用

        m_queue.pop(); // 弹出入队的第一个元素

        return true;
    }
};

class ThreadPool
{
private:
    class ThreadWorker // 内置线程工作类
    {
    private:
        int m_id; // 工作id

        ThreadPool *m_pool; // 所属线程池
    public:
        // 构造函数
        ThreadWorker(ThreadPool *pool, const int id) : m_pool(pool), m_id(id)
        {
        }

        // 重载()操作
        void operator()()
        {
            std::function<void()> func; // 定义基础函数类func

            bool dequeued; // 是否正在取出队列中元素

            while (!m_pool->m_shutdown)
            {
                {
                    // 为线程环境加锁，互访问工作线程的休眠和唤醒
                    std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);

                    // 如果任务队列为空，阻塞当前线程
                    if (m_pool->m_queue.empty())
                    {
                        m_pool->m_conditional_lock.wait(lock); // 等待条件变量通知，开启线程
                    }

                    // 取出任务队列中的元素
                    dequeued = m_pool->m_queue.dequeue(func);
                }

                // 如果成功取出，执行工作函数
                if (dequeued)
                    func();
            }
        }
    };

   bool m_shutdown; // 线程池是否关闭

    SafeQueue<std::function<void()>> m_queue; // 执行函数安全队列，即任务队列

    std::vector<std::thread> m_threads; // 工作线程队列

    std::mutex m_conditional_mutex; // 线程休眠锁互斥变量

    std::condition_variable m_conditional_lock; // 线程环境锁，可以让线程处于休眠或者唤醒状态

public:
    // 线程池构造函数
    ThreadPool(const int n_threads = 4)
        : m_threads(std::vector<std::thread>(n_threads)), m_shutdown(false)
    {
    }

    ThreadPool(const ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

    ThreadPool &operator=(ThreadPool &&) = delete;

    // Inits thread pool
    void init()
    {
        for (int i = 0; i < m_threads.size(); ++i)
        {
            m_threads.at(i) = std::thread(ThreadWorker(this, i)); // 分配工作线程
        }
    }

    // Waits until threads finish their current task and shutdowns the pool
    void shutdown()
    {
        m_shutdown = true;
        m_conditional_lock.notify_all(); // 通知，唤醒所有工作线程

        for (int i = 0; i < m_threads.size(); ++i)
        {
            if (m_threads.at(i).joinable()) // 判断线程是否在等
            {
                m_threads.at(i).join(); // 将线程加入到等待队列
            }
        }
    }

    // Submit a function to be executed asynchronously by the pool
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
        m_queue.enqueue(warpper_func);

        // 唤醒一个等待中的线程
        m_conditional_lock.notify_one();

        // 返回先前注册的任务指针
        return task_ptr->get_future();
    }
};
std::random_device rd; // 真实随机数产生器

std::mt19937 mt(rd()); //生成计算随机数mt

std::uniform_int_distribution<int> dist(-1000, 1000); //生成-1000到1000之间的离散均匀分布数

auto rnd = std::bind(dist, mt);

// 设置线程睡眠时间
void simulate_hard_computation()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

// 添加两个数字的简单函数并打印结果
void multiply(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
}

// 添加并输出结果
void multiply_output(int &out, const int a, const int b)
{
    simulate_hard_computation();
    out = a * b;
    std::cout << a << " * " << b << " = " << out << std::endl;
}

// 结果返回
int multiply_return(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
    return res;
}

void example()
{
    // 创建3个线程的线程池
    ThreadPool pool(3);

    // 初始化线程池
    pool.init();

    // 提交乘法操作，总共30个
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 10; ++j)
        {
            pool.submit(multiply, i, j);
        }
    sleep(30);
    // 使用ref传递的输出参数提交函数
    /*int output_ref;
    auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);
    // 等待乘法输出完成
    
    std::cout << "Last operation result is equals to " << output_ref << std::endl;

   // 使用return参数提交函数
    auto future2 = pool.submit(multiply_return, 5, 3);

    // 等待乘法输出完成
    int res = future2.get();
    std::cout << "Last operation result is equals to " << res << std::endl;
*/
    // 关闭线程池
    pool.shutdown();}

int main()
{
    example();

    return 0;
}