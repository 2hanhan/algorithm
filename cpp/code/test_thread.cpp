/**
 * @file test_thread.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-22
 * 线程池实现
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <chrono>

#include <vector>
#include <list>
#include <functional>

#include <thread>
#include <mutex>
#include <future>
#include <atomic>

int getRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

// 任务的基类
class XTask
{
public:
    virtual int Run() = 0;
    std::function<bool()> is_exit = nullptr;
    auto GetReturn()
    {
        return promise_result.get_future().get(); // 等待完成获取结果
    }
    void SetValue(int result)
    {
        promise_result.set_value(result);
    }

private:
    std::promise<int> promise_result; // 返回值
};


// 具体任务类
class MyTask : public XTask
{
public:
    int Run()
    {
        int run_time = 0;
        for (int i = 0; i < 10; i++)
        {
            if (is_exit())
            {
                break;
            }
            // 模仿程序随机运行一段时间
            run_time = getRand(1, 20) * 10;
            std::chrono::milliseconds wait_time(run_time);
            std::this_thread::sleep_for(wait_time);
        }
        std::cout << name << "thread id:" << std::this_thread::get_id() << std::endl;

        return run_time;
    }
    std::string name = "";
};


// 线程池
class XThreadPool
{
public:
    void Init(int num)
    {
        std::unique_lock<std::mutex> lock(mutex);
        thread_num = num;
        std::cout << " 线程池初始化，线程池线程数目" << thread_num << std::endl;
    }

    void Start()
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (thread_num <= 0)
        {
            std::cerr << " 需要初始化线程池 " << std::endl;
        }

        if (!threads.empty())
        {
            std::cerr << " 线程池已经启动 " << std::endl;
        }

        for (int i = 0; i < thread_num; i++)
        {
            std::shared_ptr<std::thread> thread_ptr = std::make_shared<std::thread>(&XThreadPool::Run, this);
            threads.push_back(thread_ptr);
        }
        std::cout << " 线程池启动" << std::endl;
    }

    void Stop()
    {
        is_exit = true;
        condition_variable.notify_all();

        for (auto &thread : threads)
        {
            thread->join();
        }
        std::unique_lock<std::mutex> lock(mutex);
        threads.clear();
        std::cout << " 线程池停止" << std::endl;
    }

    void AddTask(std::shared_ptr<XTask> task)
    {
        std::unique_lock<std::mutex> lock(mutex);
        tasks.push_back(task);
        task->is_exit = [this]()
        { return is_exit; };

        // 通知条件变量可以下一个了
        lock.unlock();
        condition_variable.notify_one();
    }

    std::shared_ptr<XTask> GetTask()
    {
        std::unique_lock<std::mutex> lock(mutex);

        if (tasks.empty())
        {
            condition_variable.wait(lock); // 等待
        }
        if (is_exit)
        {
            return nullptr;
        }
        if (tasks.empty())
        {
            return nullptr;
        }

        auto task = tasks.front();
        tasks.pop_front();
        return task;
    }

    bool IsExit()
    {
        return is_exit;
    }

    int TaskRunCount()
    {
        return task_run_num;
    }

private:
    void Run()
    {
        while (!is_exit)
        {
            auto task = GetTask();
            if (task == nullptr)
            {
                continue;
            }
            ++task_run_num;
            try
            {
                auto result = task->Run(); // 父类指针调用子类对象
                task->SetValue(result);
            }
            catch (...)
            {
            }
            --task_run_num;
        }
    }

    int thread_num = 0;                                // 线程数目
    std::vector<std::shared_ptr<std::thread>> threads; // 线程，智能指针实现自动的析构
    std::list<std::shared_ptr<XTask>> tasks;           // 任务，父类指针指向子类对象实现多态
    std::condition_variable condition_variable;        // 条件变量
    std::atomic<int> task_run_num;                     // 正在运行的任务数目,原子变量不需要上锁

    std::mutex mutex;
    bool is_exit = false; // 线程池是否退出
};

int main(int argc, char **argv)
{
    XThreadPool pool;
    pool.Init(16);
    pool.Start();

    for (int i = 0; i < 20; i++)
    {
        std::shared_ptr<MyTask> task = std::make_shared<MyTask>();
        task->name = " task" + std::to_string(i) + " ";
        pool.AddTask(task);

        if (i % 5 == 0)
        {
            std::cout << " 等待并获取计算结果:" << task->GetReturn() << std::endl;
        }
    }

    getchar();
    pool.Stop();
    std::cout << " 主线程结束 " << std::endl;
    return 0;
}