# vector

C++98下實現大部分新特性的`std::vector`

## 特色

- 支持C++98
- 支持C++20的模塊，可用`import lite.vector`导入，使用例子在`src/main.cpp`

```c++
import <cassert>;
import lite.vector;

int main()
{
    lite::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    assert(vec.size() == 3);

    return 0;
}
```

## 注意

- 不支持適配器
- 不支持`bool`特化
- 以最新標準為準
- CMake尚未支持模塊，請手動生成解決方案

高版本編譯上盡量會使用新特性實現，此時你可看作新特性使用例子。
