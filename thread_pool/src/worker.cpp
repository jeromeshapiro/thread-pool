//
// Created by Jerome Shapiro on 2018-10-19.
//

#include <functional>

#include <worker.h>

Worker::Worker(int tid) {
    thread = std::thread([=]() mutable {
        while (status != WorkerStatus::STOPPED) {
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

WorkerStatus Worker::getStatus() {
    return status;
}

void Worker::setStatus(WorkerStatus newStatus) {
    status = newStatus;
}

WorkerAssignmentFlag Worker::assignTask(Task task) {
    if (status != WorkerStatus::STOPPED) {
        tasks.push_back(task);
        return WorkerAssignmentFlag::SUCCESS;
    }

    return WorkerAssignmentFlag::FAILIURE;
}

unsigned long Worker::getBufferedTaskCount() {
    return tasks.size();
}
