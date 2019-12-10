#pragma once

#include <thread>
#include <memory>
#include <functional>
#include <atomic>
#include "ctpl_stl.h"
#include "pooled_shared.h"

namespace utility
{
    using runner_t    = std::shared_ptr<std::thread>;
    using runnerint_t = std::shared_ptr<std::atomic<bool>>;

    using runner_f_t  = std::function<void(const runnerint_t should_int)>;

    //simple way to execute lambda in thread, in case when shared_ptr is cleared it will send
    //stop notify and join(), so I can ensure 1 pointer has only 1 running thread always for the same task
    inline runner_t startNewRunner(runner_f_t func)
    {
        runnerint_t stop = pools::allocShared<std::atomic<bool>>(false);
        return  runner_t(new std::thread(func, stop), [stop](auto p)
        {
            stop->store(true);
            if (p)
            {
                if (p->joinable())
                    p->join();
                delete p;
            }
        });
    }

    inline size_t currentThreadId()
    {
        return std::hash<std::thread::id> {}(std::this_thread::get_id());
    }
}

