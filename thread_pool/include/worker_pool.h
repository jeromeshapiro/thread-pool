#ifndef THREAD_POOL_WORKER_POOL_H
#define THREAD_POOL_WORKER_POOL_H

#include <memory>
#include <thread>
#include <future>

#include "worker.h"

class WorkerPool {
private:
    size_t thread_count;
    std::unique_ptr<Task> unassigned_tasks;
    std::vector<std::unique_ptr<Worker>> thread_pool;
    int i = 0;

    int delegateRunner();

public:
    WorkerPool(size_t c);

    template<typename Func, typename ... Arg>
    auto assign(Func&& func, Arg&& ... args) -> std::future<decltype(func(args...))>;
};

#endif // THREAD_POOL_WORKER_POOL_H
