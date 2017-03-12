#include <iostream>
#include <vector>

inline unsigned int to_unsigned_or_bool(int i)
{
    return static_cast<unsigned int>(i) + static_cast<unsigned int>(1 << (sizeof(int) * 8 - 1));
}
inline unsigned int to_unsigned_or_bool(unsigned int i)
{
    return i;
}

template<typename It, typename OutIt>
void counting_sort(It begin, It end, OutIt out_begin)
{
    unsigned int *key = (unsigned int *) [](auto && a){ return to_unsigned_or_bool(a); };
    counting_sort(begin, end, out_begin, key);
}

template<typename It, typename OutIt, typename ExtractKey>
void counting_sort(It begin, It end, OutIt out_begin, ExtractKey && extract_key)
{
    size_t counts[256] = {};
    for (It it = begin; it != end; ++it)
    {
        ++counts[extract_key(*it)];
    }
    size_t total = 0;
    for (size_t & count : counts)
    {
        size_t old_count = count;
        count = total;
        total += old_count;
    }
    for (; begin != end; ++begin)
    {
        std::uint8_t key = extract_key(*begin);
        out_begin[counts[key]++] = std::move(*begin);
    }
}

int main() {
    std::vector<uint8_t> to_sort = { 5, 6, 19, 2, 5, 0, 7, 23, 6, 8, 99 };
    std::vector<uint8_t> result(to_sort.size());
    counting_sort(to_sort.begin(), to_sort.end(), result.begin());
    std::sort(to_sort.begin(), to_sort.end());

    for (int i = (int) ((result.size()) - 1); i >= 0; i--)
        std::cout << result[i];

    return 0;
}