#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <vector>

class thread_pool
{

    private:
        std::vector<std::thread> workers;
        std::mutex mutex;
        std::condition_variable cv;
        std::queue<std::function<void()>> queue;
        bool stop;

    public:
        thread_pool(std::size_t num_threads = std::thread::hardware_concurrency())
        {
            
            stop = false;
            for(auto i =  0; i < num_threads; i++)
            {
                workers.emplace_back(&thread_pool::worker, this);
            }
        
        }

        ~thread_pool()
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                stop = true;  
            }

            cv.notify_all();
            for(auto& worker : workers)
            {
                worker.join();
            }
           
        }

        template<typename F, typename... Args>
        inline auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
        {
            auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            auto encapsulated_ptr = 
                std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

            std::future<decltype(f(args...))> future_object = encapsulated_ptr -> get_future();
            {
                std::unique_lock<std::mutex> lock(mutex);
                queue.emplace([encapsulated_ptr](){
                    (*encapsulated_ptr)();
                });
            }
            cv.notify_one();
            return future_object;
        }

        thread_pool(thread_pool&) = delete;
        thread_pool(const thread_pool&) = delete;
        thread_pool& operator = (thread_pool&&) = delete;
        thread_pool& operator = (const thread_pool&) = delete;


        void worker()
        {
            for(;;)
            {
                std::function<void()> cur_task;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    cv.wait(lock, [this]() {
                        return stop || !queue.empty();
                    });

                    if(stop && queue.empty())
                        break;
                    if(queue.empty())
                        continue;

                    cur_task = queue.front();
                    queue.pop();
                }
                cur_task();
            }
        }
};

#endif
