#include <vector> // std::vector
#include <lite/vector.hpp>
#include <cstring> // memcmp
#include <cassert> // std::assert
#include <iostream>
#include <type_traits>
#include <Windows.h>

struct Int
{
    Int(int data)
        : m_data(data)
    {
    }
    ~Int()
    {
    }
    int m_data = 0;
};

struct Object
{
    //Object() = default;
    Object(int _value)
        : value(_value)
    {
    }
    ~Object()
    {
        std::cout << __FUNCTION__ << ": " << value << std::endl;
    }
    int value = 0;
};

int main()
{
    lite::vector<char> vec;
    vec.push_back('1');
    vec.push_back('2');
    vec.push_back('3');
    assert(memcmp(vec.data(), "123", vec.size()) == 0);

    //std::vector<Int> svec;
    //svec.emplace_back(1);
    //lite::vector<Int> lvec;
    //lvec.emplace_back(1);

    //auto o1 = new Object;
    //auto o1 = (Object*)malloc(sizeof(Object));
    //if (o1 != nullptr)
    //{
    //    o1->value = 1;
    //    delete o1;
    //}

    auto obj = reinterpret_cast<Object*>(new char[sizeof(Object)]);
    new (obj) Object(100);
    obj->~Object();

    std::cout << std::is_trivial<int>::value << std::endl;
    std::cout << std::is_trivial<BYTE>::value << std::endl;
    std::cout << std::is_trivial<Object>::value << std::endl;

    auto i = reinterpret_cast<int*>(new char[sizeof(int)]);
    new (i) int(99);
    delete[] i;

    lite::vector<Object> v;
    v.emplace_back(999);

    {
        std::vector<Object> v;
        v.emplace_back(888);
    }

    return 0;
}
