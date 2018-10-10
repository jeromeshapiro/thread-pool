#include <iostream>
#include <thread>
#include <sstream>
#include <memory>
#include <vector>
#include <functional>

#include <unistd.h>

static const uint count = 5;

void test_func(int i) {
    std::cout << "func " << std::endl;
}

template<typename F>
class Thread {
    private:
        std::thread _thread;
        std::vector<std::function<F>> _tasks;
        bool _active = true;
        bool _notified = false;
    public:
        Thread(int tid) {
            std::cout << "spawning thread " << tid << std::endl;

            _thread = std::thread([=]() mutable {
                while (_active == true) {
                    if (_notified == false) {
                        std::cout << "polling for tasks on thread " << tid << std::endl;
                        _notified = true;
                    }

                    if (!_tasks.empty()) {
                        // get task
                        auto task = _tasks.front();

                        // run task
                        task();

                        // destroy task
                        _tasks.front() = _tasks.back();
                        _tasks.pop_back();
                    }
                }
            });
        }

        void assign(std::function<F> task) {
            _tasks.push_back(task);
        }
};

template<typename F>
class ThreadPool {
    private:
        size_t _thread_count;
        std::unique_ptr<Thread<F>> _thread_pool[count];
        std::vector<std::function<F>> _unassigned_tasks;

    public:
        ThreadPool(size_t thread_count) :
            _thread_count(thread_count)
        {
            auto tid = 0;

            for (auto &_thread : _thread_pool) {
                _thread = std::make_unique<Thread<F>>(tid++);
            }
        }

        void assign(std::function<F> task) {
            _thread_pool[0]->assign(std::bind(task, 1));
        }
};

int main() {
    auto threadPool = std::make_unique<ThreadPool<void(int)>>(5);

    usleep(3000000);

    threadPool->assign(test_func);
    threadPool->assign(test_func);
    threadPool->assign(test_func);

    usleep(3000000);

    return 0;
}
