#ifndef ADASTRA_THREADPOOL_HPP
#define ADASTRA_THREADPOOL_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <unordered_map>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <pthread.h>
#include <shared_mutex>

namespace Adastra
{
    // Structure pour gérer les tâches avec priorité
    struct Task
    {
        std::function<void()> func;
        int priority;

        bool operator<(const Task &other) const;
    };

    thread_local int threadId = -1; // Thread Local Storage pour identifier chaque thread

    class ThreadPool
    {
    private:
        std::vector<std::thread> workers;
        std::priority_queue<Task> tasks;
        std::mutex m;
        std::condition_variable condition;
        std::atomic<bool> stop;
        std::atomic<bool> stopPeriodic;
        size_t maxThreads;
        std::unordered_map<std::thread::id, int> threadAffinity;
        std::atomic<int> activeTasks;

        // Fonction pour affecter une affinité CPU à un thread
        void setThreadAffinity(int id);

    public:
        ThreadPool(size_t threadCount, size_t maxThreadCount);

        // Fonction pour créer un nouveau thread
        void createThread(int id);

        template <class F, class... Args>
        auto enqueue(int priority, F &&f, Args &&...args) -> std::future<typename std::invoke_result<F, Args...>::type>;

        void periodicTask(int priority, std::function<void()> func, std::chrono::milliseconds interval);

        bool isIdle();

        void stopPeriodicTasks();

        ~ThreadPool();
    };
} // namespace Adastra

#endif // ADASTRA_THREADPOOL_HPP
