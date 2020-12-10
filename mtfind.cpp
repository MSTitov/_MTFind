#include "stdafx2.h"

const int N = 100;
std::mutex mtx;

struct occurrences
{
    occurrences() 
        : line("0"),
        pos_in_line(0),
        str("NOON") {
    }
    std::string line;
    int pos_in_line;
    std::string str;
};

namespace tools
{
    namespace detail_match_pattern
    {        
        template<class ch>
        occurrences match_pattern(const ch* s, const ch* p) noexcept
        {
            assert(s);
            assert(p);

            std::unique_lock<std::mutex> ul(mtx);

            const ch* rp = p;
            occurrences match;
            std::string _s, _line;
            int _pos = 0, sp = -2;           
            
            while (*s)
            {
                if (*s == ' ')
                    ++sp,
                    _s.clear();

                else if (isdigit(*s))
                    _line += *s;

                else
                {
                    if (*s == *p || *p == '?')
                    {                        
                        ++p;
                        _s += *s;
                        if (!*p)
                            match.line = _line,
                            match.pos_in_line = _pos / 2 + sp,
                            match.str = _s;
                    }
                    else if (s)
                        --s,
                        p = rp;
                    ++_pos;
                }
                ++s;
            }

            ul.unlock();

            return match;
        }

    }//namespace detail_match_pattern

    template<class s1, class s2>
    occurrences match_pattern(const s1& text, const s2& pattern) noexcept
    {
        return detail_match_pattern::match_pattern(
            &text[0], &pattern[0]
        );
    }

} // namespace tools

int main(int argc, char* argv[])
{
    const char mask[N] = "?ad";
    std::ifstream fis("input.txt", std::ios_base::in | std::ios_base::app);

    if (!fis.is_open())
    {
        std::cerr << "Could not open Client.txt\n";
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

    std::cout << counter << std::endl;
    for (const auto& s : match)
    {
        std::cout << s.line << " " << s.pos_in_line
            << " " << s.str << std::endl;
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
    
    delete[] p;
    fis.clear();
    fis.close();

    return 0;
}