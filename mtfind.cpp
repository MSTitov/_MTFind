#include "log_duration.h"
#include "match_pattern.h"

const int N = 100;

std::ostream& operator<<(std::ostream& os, 
    const std::vector<occurrences>& v_match)
{
    for (const auto& s : v_match)
    {
        os << s.line << " " << s.pos_in_line
            << " " << s.str << std::endl;
    }
    return os;
}

int main(int argc, char* argv[]) 
{
    LOG_DURATION("threads execution ");


    const char mask[N] = "?ad";
    std::ifstream fis("input.txt", std::ios_base::in | std::ios_base::app);

    if (!fis.is_open())
    {
        std::cerr << "Could not open input.txt\n";
        fis.clear();
    }

    std::vector<std::thread> threads;
    std::vector<occurrences> match;
    char* p = new char[1024];
    int counter = 0;
    
    while (fis.getline(p, 1024))
    {
        std::promise<void> promise;
        auto waiter = promise.get_future();
        occurrences success;

        std::thread thread([&]
        {
            success = tools::match_pattern(p, mask);
            promise.set_value();
        });
        threads.emplace_back(std::move(thread));
        
        waiter.wait();
        if (success.pos_in_line)
            ++counter,
            match.push_back(success);
    }

    std::cout << counter << std::endl
        << match << std::endl;

    for (auto& thread : threads)
    {
        thread.join();
    }
    
    delete[] p;
    fis.clear();
    fis.close();

    return 0;
}