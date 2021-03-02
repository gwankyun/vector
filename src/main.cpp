#include <lite/vector.hpp>
#include <cstring> // memcmp
#include <cassert> // std::assert

int main()
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    assert(memcmp(vec.data(), "123", vec.size()) == 0);
    return 0;
}
