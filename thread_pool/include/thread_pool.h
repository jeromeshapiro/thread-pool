//
// Created by Jerome Shapiro on 2018-10-19.
//

#ifndef THREAD_POOL_THREAD_POOL_H
#define THREAD_POOL_THREAD_POOL_H

#include <memory>
#include <thread>
#include <future>

#include "runner.h"

class ThreadPool {
private:
    size_t thread_count;
    std::unique_ptr<Task> unassigned_tasks;
    std::vector<std::unique_ptr<Runner>> thread_pool;
    int i = 0;

    int delegateRunner();

public:
    ThreadPool(size_t c);

    template<typename Func, typename ... Arg>
    auto assign(Func&& func, Arg&& ... args) -> std::future<decltype(func(args...))>;
};

#endif //THREAD_POOL_THREAD_POOL_H
