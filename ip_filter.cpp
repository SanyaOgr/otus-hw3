#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using IpType = std::vector<std::string>;

using IpPoolType = std::vector<IpType>;

template<int startIndex, int endIndex>
auto ipPartialGreaterComp(const IpType& lhs, const IpType& rhs)
{
    for (int i = startIndex; i < endIndex; ++i)
    {
        if (lhs[i] == rhs[i]) continue;
        return std::greater<decltype(lhs[i])>{}(lhs[i], rhs[i]);
    }
    return false;
}

auto ipGreaterComp = ipPartialGreaterComp<0, 4>;

auto split(const std::string &str, char d)
{
    auto r = IpType{};

    auto start = std::string::size_type{};
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

auto print(const IpPoolType& ip_pool)
{
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

auto filter(const IpPoolType& ip_pool, int first_part)
{
    auto startIt = std::lower_bound(ip_pool.cbegin(), ip_pool.cend(), IpType{ std::to_string(first_part), "0", "0", "0" }, ipPartialGreaterComp<0, 1>);
    auto endIt = std::upper_bound(ip_pool.cbegin(), ip_pool.cend(), IpType{ std::to_string(first_part), "0", "0", "0" }, ipPartialGreaterComp<0, 1>);

    return IpPoolType(startIt, endIt);
}


int main(int argc, char const *argv[])
{
    try
    {
        auto ip_pool = IpPoolType{};

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // Reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), ipGreaterComp);

        // Print
        print(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // Filter by first byte and output
        auto ip = filter(ip_pool, 1);
        print(ip);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
