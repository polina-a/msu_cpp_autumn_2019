//Реализовать пул потоков 

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>


class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize): working(true) {
    for (size_t i = 0; i < poolSize; ++i) {
        all_threads.emplace_back(
                [this]() {
                    while (working) {
                        std::unique_lock<std::mutex> lock(m);
                        if (!taskQueue.empty()) {
                            auto task = taskQueue.front();
                            taskQueue.pop();
                            lock.unlock();
                            task();
                        } else {
                            var.wait(lock);
                        }
                    }
                });
    }
}

    ~ThreadPool() {
        working = false;
        var.notify_all();
        for (auto& thread : all_threads) {
            thread.join();
        }
    }

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        using ReturnType = decltype(func(args...));
		using PackagedType = std::packaged_task<ReturnType ()>;
		auto task = std::make_shared<PackagedType>([func, args...](){
			return func(args...);
		});
		{
			std::lock_guard<std::mutex> lock(m);
			taskQueue.emplace(
					[task]() {
						(*task)();
					});
		}
		var.notify_one();
		return task->get_future();
	}
private:
    using Task = std::function<void ()>;
    std::atomic<bool> working;
	std::queue<Task> taskQueue;
    std::condition_variable var;
	std::vector<std::thread> all_threads;
	std::mutex m;    
};