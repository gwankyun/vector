#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <lite/vector.hpp> // std::fill_n
#include <cstring> // std::memcmp
#include <algorithm>

TEST_CASE("push_back", "lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    REQUIRE(vec.size() == 3);
}

TEST_CASE("emplace_back", "lite::vector")
{
    struct Int
    {
        Int(int _data)
            : value(_data)
        {
        }
        Int(const Int&) = delete;
        ~Int()
        {
        }
        int value;
    };
    lite::vector<Int> vec;
    vec.emplace_back(1);
    vec.emplace_back(2);
    vec.emplace_back(3);
    REQUIRE(vec.size() == 3);
}

TEST_CASE("pop_back", "lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.pop_back();
    vec.pop_back();
    REQUIRE(vec.size() == 1);
}

TEST_CASE("clear & empty", "lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.pop_back();
    vec.clear();
    REQUIRE(vec.empty());
}

TEST_CASE("data", "lite::vector")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    REQUIRE(std::memcmp(vec.data(), "123", vec.size()) == 0);
}

TEST_CASE("resize", "lite::vector")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    vec.resize(5, '0');
    REQUIRE(std::memcmp(vec.data(), "12300", vec.size()) == 0);
}

TEST_CASE("reserve", "lite::vector")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    vec.reserve(5);
    REQUIRE((vec.size() == 3 && vec.capacity() == 5));
}

TEST_CASE("iterator", "lite::vector")
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

    REQUIRE(*b == 1);
    REQUIRE(*rb == 3);
    REQUIRE(*(e - 1) == 3);
    REQUIRE(*(re + 1) == 1);

    REQUIRE(*cb == 1);
    REQUIRE(*crb == 3);
    REQUIRE(*(ce - 1) == 3);
    REQUIRE(*(cre + 1) == 1);
}

TEST_CASE("front & back", "lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    REQUIRE(vec.front() == 1);
    REQUIRE(vec.back() == 3);
}

TEST_CASE("[] & at", "lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec.at(2) == 3);
}

TEST_CASE("insert", "lite::vector")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    auto iter = vec.begin();
    iter++;
    vec.insert(iter, '0');
    REQUIRE(std::memcmp(vec.data(), "1023", vec.size()) == 0);
    iter = vec.begin();
    iter++;
    vec.insert(iter, 2, '4');
    REQUIRE(std::memcmp(vec.data(), "144023", vec.size()) == 0);
}

TEST_CASE("erase", "lite::vector")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    auto iter = vec.begin();
    iter++;
    vec.erase(iter);
    REQUIRE(std::memcmp(vec.data(), "13", vec.size()) == 0);
    vec.push_back('4');
    vec.push_back('5');
    iter = vec.begin();
    auto lst = iter + 2;
    vec.erase(iter, lst);
    REQUIRE(std::memcmp(vec.data(), "45", vec.size()) == 0);
    REQUIRE(vec.erase(vec.begin() + vec.size() - 1) == vec.end());
}

TEST_CASE("fill_n", "lite::vector")
{
    lite::vector<char> vec;
    vec.resize(3, 'a');
    std::fill_n(vec.begin(), vec.size(), 'c');
    REQUIRE(std::memcmp(vec.data(), "ccc", vec.size()) == 0);
}

TEST_CASE("swap", "lite::vector")
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
    REQUIRE(std::memcmp(vec1.data(), "456", vec1.size()) == 0);
    REQUIRE(std::memcmp(vec2.data(), "123", vec2.size()) == 0);
    lite::swap(vec1, vec2);
    REQUIRE(std::memcmp(vec1.data(), "123", vec1.size()) == 0);
    REQUIRE(std::memcmp(vec2.data(), "456", vec2.size()) == 0);
}
