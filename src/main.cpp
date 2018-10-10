#include <iostream>
#include <thread>
#include <sstream>
#include <memory>
#include <vector>
#include <functional>

#include <unistd.h>

static const uint count = 5;

void test_func_1(int i) {
    std::cout << "func 1: " << i << std::endl;
}

void test_func_2(int i, int j) {
    std::cout << "func 2: " << i << " | " << j << std::endl;
}

typedef std::function<void()> Task;

class Thread {
    private:
        std::thread _thread;
        std::vector<Task> _tasks;
        bool _active = true;
    public:
        Thread(int tid) {
            _thread = std::thread([=]() mutable {
                while (_active == true) {
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

        void assign(Task task) {
            _tasks.push_back(task);
        }
};

class ThreadPool {
    private:
        size_t _thread_count;
        std::unique_ptr<Thread> _thread_pool[count];
        std::vector<Task> _unassigned_tasks;

    public:
        ThreadPool(size_t thread_count) :
            _thread_count(thread_count)
        {
            auto tid = 0;

            for (auto &_thread : _thread_pool) {
                _thread = std::make_unique<Thread>(tid++);
            }
        }
        
        template<typename Func, typename ... Arg>
        void assign(Func function, Arg ... arg) {
            _thread_pool[0]->assign([=](){
                function(arg...);
            });
        }
};

int main() {
    auto threadPool = std::make_unique<ThreadPool>(5);

    threadPool->assign(test_func_1, 0);
    threadPool->assign(test_func_2, 1, 11);
    threadPool->assign(test_func_2, 2, 22);

    std::cin.get();

    return 0;
}
