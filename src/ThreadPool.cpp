#include "Adastra/ThreadPool.hpp"

namespace Adastra
{
    bool Task::operator<(const Task &other) const
    {
        return priority < other.priority; // Plus grande priorité en haut de la queue
    }

    ThreadPool::ThreadPool(size_t threadCount, size_t maxThreadCount)
        : stop(false), stopPeriodic(false), maxThreads(maxThreadCount), activeTasks(0)
    {
        for (size_t i = 0; i < threadCount; ++i)
        {
            createThread(i);
        }
    }

    void ThreadPool::createThread(int id)
    {
        workers.emplace_back([this, id]
                             {
            threadId = id;
            threadAffinity[std::this_thread::get_id()] = id;

            setThreadAffinity(id);  // Configurer l'affinité du thread

            while (true) {
                Task task;
                {
                    std::unique_lock<std::mutex> lock(m);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });

                    if (stop && tasks.empty()) return;

                    task = std::move(tasks.top());
                    tasks.pop();
                    ++activeTasks;
                }
                try {
                    task.func();
                } catch (const std::exception& e) {
                    std::cerr << "Exception dans le thread " << threadId << ": " << e.what() << std::endl;
                }
                --activeTasks;
                condition.notify_one();
            } });
    }

    template <class F, class... Args>
    auto ThreadPool::enqueue(int priority, F &&f, Args &&...args) -> std::future<typename std::invoke_result<F, Args...>::type>
    {
        using ReturnType = typename std::invoke_result<F, Args...>::type;
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<ReturnType> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(m);
            tasks.push({[task]()
                        {
                            try
                            {
                                (*task)();
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "Exception dans la tâche : " << e.what() << std::endl;
                            }
                        },
                        priority});

            if (workers.size() < maxThreads)
            {
                createThread(workers.size());
            }
        }
        condition.notify_one();
        return res;
    }

    void ThreadPool::periodicTask(int priority, std::function<void()> func, std::chrono::milliseconds interval)
    {
        auto loop = [this, priority, func, interval]()
        {
            while (!stopPeriodic)
            {
                try
                {
                    auto future = enqueue(priority, func);
                    if (future.wait_for(interval) == std::future_status::timeout)
                    {
                        std::cerr << "Tâche périodique annulée pour dépassement du temps limite." << std::endl;
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Exception dans la tâche périodique : " << e.what() << std::endl;
                }
                std::this_thread::sleep_for(interval);
            }
        };
        std::thread(loop).detach();
    }

    bool ThreadPool::isIdle()
    {
        return activeTasks.load() == 0 && tasks.empty();
    }

    void ThreadPool::stopPeriodicTasks()
    {
        stopPeriodic = true;
    }

    void ThreadPool::setThreadAffinity(int id)
    {
#ifdef __linux__
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(id % std::thread::hardware_concurrency(), &cpuset);
        pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
#endif
    }

    ThreadPool::~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(m);
            stop = true;
            stopPeriodic = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers)
        {
            if (worker.joinable())
            {
                worker.join();
            }
        }
    }
} // namespace Adastra
