#pragma once

#ifndef LOG_DURATION_
#define LOG_DURATION_

#include "stdafx2.h"

#define PROFILE_CONCAT_INTERNAL(X, Y) X##Y
#define PROFILE_CONCAT(X, Y) PROFILE_CONCAT_INTERNAL(X, Y)
#define UNIQUE_VAR_NAME_PROFILE PROFILE_CONCAT(profileGuard, __LINE__)
#define LOG_DURATION(x) LogDuration UNIQUE_VAR_NAME_PROFILE(x)

class LogDuration
{
public:
    using Clock = std::chrono::steady_clock;

    explicit LogDuration(const std::string& id)
        : id_(id) {
    }

    ~LogDuration()
    {
        using namespace std::chrono;
        using namespace std::literals;

        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        std::cerr << id_ << ": " << duration_cast<milliseconds>(dur).count() << " ms" << std::endl;
    }

private:
    const std::string id_;
    const Clock::time_point start_time_ = Clock::now();
};


#endif // !LOG_DURATION_