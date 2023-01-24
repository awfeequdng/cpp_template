#include <iostream>
#include "my_traits.hh"
#include <cassert>

void test_is_same() {
    std::cout << __FUNCTION__ << std::endl;
    auto a = my_traits::is_same_v<int, int&> == false;
    auto b = my_traits::is_same_v<int, const int&> == false;
    auto c = my_traits::is_same_v<int, int> == true;
    assert(a);
    assert(b);
    assert(c);
    a = my_traits::is_same<int, int&>::value == false;
    b = my_traits::is_same<int, const int&>::value == false;
    c = my_traits::is_same<int, int>::value == true;
    assert(a);
    assert(b);
    assert(c);
}

void test_remove_const() {
    std::cout << __FUNCTION__ << std::endl;

}

void test_remove_reference() {
    std::cout << __FUNCTION__ << std::endl;
    std::cout << typeid(int &).name() << std::endl;
    std::cout << typeid(int).name() << std::endl;
    std::cout << typeid(const int &).name() << std::endl;
    // 上面三个的typeid相同的
    assert(typeid(int) == typeid(my_traits::remove_reference<int &>::type));
    assert(typeid(int &).name() == typeid(my_traits::remove_reference<int &>::type).name());

    int a = 0;
    my_traits::remove_reference<int &>::type b = a;
    my_traits::remove_reference<int &>::type c = 0;
    decltype(b) d = 0;
    my_traits::remove_const<int &>::type e = d;
    my_traits::remove_const<const int>::type f = d;
    const int g = e; // 这个怎么不报错
    const int tt = 2;
    my_traits::remove_const<const int &>::type h = d;
    const int i =tt;
    char cd[i] = {0};
}

int main() {
    test_is_same();
    test_remove_reference();
    test_remove_const();

    return 0;
}
