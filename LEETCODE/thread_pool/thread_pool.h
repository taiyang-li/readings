//
// Created by Li,Yang(CPD) on 19/4/30.
//

#ifndef LEETCODE_SRC_THREAD_POOL_H
#define LEETCODE_SRC_THREAD_POOL_H
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <future>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <utility>

class ThreadPool {

public:
    ThreadPool(int size);
    ~ThreadPool();

    template <class F, class... Args>
    auto enqueue(F&& f, Args... args)
        -> std::future<typename  std::result_of<F(Args...)>::type>;
private:
    // 线程组
    std::vector<std::thread> _threads;

    // 任务队列
    std::queue<std::function<void()> > _tasks;

    // 停止开关
    bool _stop;

    // 线程同步
    std::mutex _mutex;
    std::condition_variable _condition;
};

ThreadPool::ThreadPool(int size) {
    _stop = false;
    _threads.reserve(size);
    for (int i=0; i<size; ++i) {
        _threads.emplace_back([this] {
            while (1) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->_mutex);

                    this->_condition.wait(lock, [this] {
                        return this->_stop || !this->_tasks.empty();
                    });
                    if (this->_stop && this->_tasks.empty()) {
                        return;
                    }

                    task = std::move(this->_tasks.front());
                    this->_tasks.pop();
                }
                task();
            }
        });
    }
}

template <class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args... args)
    -> std::future<typename  std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type ()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(_mutex);
        if (_stop) {
            throw std::runtime_error("enqueue on stopped threadpool");
        }

        _tasks.emplace([task] {
            (*task)();
        });
    }
    return res;
};

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _stop = true;
    }

    _condition.notify_all();
    for (auto& thread: _threads) {
        thread.join();
    }
}

#endif //LEETCODE_SRC_THREAD_POOL_H
