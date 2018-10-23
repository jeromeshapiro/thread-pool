//
// Created by Jerome Shapiro on 2018-10-19.
//

#ifndef THREAD_POOL_RUNNER_H
#define THREAD_POOL_RUNNER_H

#include <functional>
#include <thread>
#include <vector>

typedef std::function<void()> Task;

class Runner {
private:
    std::thread thread;
    std::vector<Task> tasks;
    bool active = true;
public:
    Runner(int tid);
    void assign(Task task);
};

#endif //THREAD_POOL_RUNNER_H
