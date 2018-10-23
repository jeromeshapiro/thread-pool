//
// Created by Jerome Shapiro on 2018-10-19.
//

#include <memory>
#include <future>
#include <functional>

#include <worker_pool.h>
#include <worker.h>

int WorkerPool::delegateRunner() {
    if (i == thread_count) {
        i = 0;
    }

    return i++;
}

WorkerPool::WorkerPool(size_t c) : thread_count(c), thread_pool(c) {
    for (auto i = 0; i < thread_count; i++) {
        thread_pool[i] = std::make_unique<Worker>(i);
    }
}

template<typename Func, typename ... Arg>
auto WorkerPool::assign(Func&& func, Arg&& ... args) -> std::future<decltype(func(args...))> {
    std::function<decltype(func(args...))()> callable = std::bind(std::forward<Func>(func),
            std::forward<Arg>(args)...);

    auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(callable);

    auto delegatedRunner = delegateRunner();

    thread_pool[delegatedRunner]->assignTask([task]() {
        (*task)();
    });

    return task->get_future();
}