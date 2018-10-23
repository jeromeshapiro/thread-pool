#ifndef THREAD_POOL_WORKER_H
#define THREAD_POOL_WORKER_H

#include <functional>
#include <thread>
#include <vector>

typedef std::function<void()> Task;

typedef enum {
    ACTIVE, // Worker will accept new tasks to its buffer and will continue to execute buffered tasks
    PAUSED, // Worker will accept new tasks to its buffer but will not execute buffered tasks
    STOPPED, // Worker will not accept new tasks and will continue to execute buffered tasks until drained
} WorkerStatus;

typedef enum {
    SUCCESS,
    FAILIURE,
} WorkerAssignmentFlag;

class Worker {
private:
    std::thread thread;
    std::vector<Task> tasks;
    WorkerStatus status = WorkerStatus::ACTIVE;
public:
    Worker(int tid);
    WorkerStatus getStatus();
    void setStatus(WorkerStatus status);
    WorkerAssignmentFlag assignTask(Task task);
    unsigned long getBufferedTaskCount();
};

#endif // THREAD_POOL_WORKER_H
