#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <lite/vector.hpp>
#include <cstring>

TEST_CASE("push_back", "lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
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
    REQUIRE(memcmp(vec.data(), "123", vec.size()) == 0);
}

TEST_CASE("resize", "lite::vector")
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    vec.resize(5, '0');
    REQUIRE(memcmp(vec.data(), "12300", vec.size()) == 0);
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

TEST_CASE("[]", "lite::vector")
{
    lite::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    REQUIRE(vec[1] == 2);
}
