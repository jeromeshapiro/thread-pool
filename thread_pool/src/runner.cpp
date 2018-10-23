//
// Created by Jerome Shapiro on 2018-10-19.
//

#include <functional>

#include <runner.h>

Runner::Runner(int tid) {
    thread = std::thread([=]() mutable {
        while (active) {
            if (!tasks.empty()) {
                // get task
                auto task = tasks.front();
                // run task
                task();
                // destroy task
                tasks.front() = tasks.back();
                tasks.pop_back();
            }
        }
    });

    thread.detach();
}

void Runner::assign(Task task) {
    tasks.push_back(task);
}

bool Runner::isActive() {
    return active;
}
