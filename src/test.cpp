module;
#include <cstring> // std::memcmp
#include <algorithm>
#include <iostream>
#include <lite/vector.hpp> // std::fill_n
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
module main;

int main(int argc, char* argv[])
{
    doctest::Context context;

    context.applyCommandLine(argc, argv);

    context.setOption("no-breaks", true);

    int res = context.run();

    if (context.shouldExit())
    {
        return res;
    }

    context.clearFilters();

    return res;
}

TEST_CASE("lite::vector")
{
    CHECK(!IS_CLASS_V(int));

    lite::vector<int> v1;
    CHECK(v1.empty());

    lite::vector<int> v2(8);
    CHECK(v2.size() == 8);

    struct Int
    {
        Int(int) {}
        ~Int() {}
    private:
        Int(const Int&) {}
    };
    CHECK(IS_CLASS_V(Int));

    lite::vector<Int> v3;
    CHECK(v3.empty());

    lite::vector<Int> v4(8);
    CHECK(v4.size() == 8);
}

TEST_CASE("lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    CHECK(vec.size() == 3);
}

TEST_CASE("emplace_back")
{
#if CXX_VER >= 2011
    struct Int
    {
        Int(int _data)
            : value(_data)
        {
        }
        Int(const Int&) = delete;
        ~Int() = default;
        int value;
    };
    CHECK(IS_CLASS_V(Int));
    lite::vector<Int> vec;
    vec.emplace_back(1);
    vec.emplace_back(2);
    vec.emplace_back(3);
    CHECK(vec.size() == 3);
#endif
}

TEST_CASE("pop_back")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.pop_back();
    vec.pop_back();
    CHECK(vec.size() == 1);
}

TEST_CASE("clear & empty")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.pop_back();
    vec.clear();
    CHECK(vec.empty());
}

TEST_CASE("data")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    CHECK(std::memcmp(vec.data(), "123", vec.size()) == 0);
}

TEST_CASE("resize")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    vec.resize(5, '0');
    CHECK(std::memcmp(vec.data(), "12300", vec.size()) == 0);
}

TEST_CASE("reserve")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    vec.reserve(5);
    CHECK((vec.size() == 3 && vec.capacity() == 5));
}

TEST_CASE("iterator")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    auto b = vec.begin();
    auto rb = vec.rbegin();
    auto e = vec.end();
    auto re = vec.rend();

    auto cb = vec.cbegin();
    auto crb = vec.crbegin();
    auto ce = vec.cend();
    auto cre = vec.crend();

    CHECK(*b == 1);
    CHECK(*rb == 3);
    CHECK(*(e - 1) == 3);
    CHECK(*(re + 1) == 1);

    CHECK(*cb == 1);
    CHECK(*crb == 3);
    CHECK(*(ce - 1) == 3);
    CHECK(*(cre + 1) == 1);
}

TEST_CASE("front & back")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    CHECK(vec.front() == 1);
    CHECK(vec.back() == 3);
}

TEST_CASE("[] & at")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    CHECK(vec[1] == 2);
    CHECK(vec.at(2) == 3);
}

TEST_CASE("insert")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    auto iter = vec.begin();
    iter++;
    vec.insert(iter, '0');
    CHECK(std::memcmp(vec.data(), "1023", vec.size()) == 0);
    iter = vec.begin();
    iter++;
    vec.insert(iter, 2, '4');
    CHECK(std::memcmp(vec.data(), "144023", vec.size()) == 0);
}

TEST_CASE("erase")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    auto iter = vec.begin();
    iter++;
    vec.erase(iter);
    CHECK(std::memcmp(vec.data(), "13", vec.size()) == 0);
    vec.push_back('4');
    vec.push_back('5');
    iter = vec.begin();
    auto lst = iter + 2;
    vec.erase(iter, lst);
    CHECK(std::memcmp(vec.data(), "45", vec.size()) == 0);
    iter = vec.erase(vec.begin(), vec.begin() + vec.size());
    CHECK(iter == vec.end());
}

TEST_CASE("fill_n")
{
    lite::vector<char> vec;
    vec.resize(3, 'a');
    std::fill_n(vec.begin(), vec.size(), 'c');
    CHECK(std::memcmp(vec.data(), "ccc", vec.size()) == 0);
}

TEST_CASE("swap")
{
    lite::vector<char> vec1;
    vec1.push_back('1');
    vec1.push_back('2');
    vec1.push_back('3');
    lite::vector<char> vec2;
    vec2.push_back('4');
    vec2.push_back('5');
    vec2.push_back('6');
    vec1.swap(vec2);
    CHECK(std::memcmp(vec1.data(), "456", vec1.size()) == 0);
    CHECK(std::memcmp(vec2.data(), "123", vec2.size()) == 0);
    lite::swap(vec1, vec2);
    CHECK(std::memcmp(vec1.data(), "123", vec1.size()) == 0);
    CHECK(std::memcmp(vec2.data(), "456", vec2.size()) == 0);
}
