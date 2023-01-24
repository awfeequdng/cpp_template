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
    // 上面三个的typeid相同的
    const int i = 0;
    const int &j = i;
    auto a = my_traits::is_same<int, my_traits::remove_const_t<const int>>::value;
    auto b = my_traits::is_same_v<int, my_traits::remove_const_t<decltype(i)>>;
    auto d = my_traits::is_same_v<int, my_traits::remove_const_t<my_traits::remove_reference_t<decltype(j)>>>; // 为什么这个会报错
    // 为什么const int &中的const没有被remove掉？？？？
    // todo:
    auto c = my_traits::is_same_v<const int &, my_traits::remove_const_t<decltype(j)>>;
    auto e = my_traits::is_same_v<const int &, std::remove_const_t<decltype(j)>>;
    assert(a);
    assert(b);
    assert(d);
    assert(c);
    assert(e);
}

void test_remove_reference() {
    std::cout << __FUNCTION__ << std::endl;
    std::cout << typeid(int &).name() << std::endl;
    std::cout << typeid(int).name() << std::endl;
    std::cout << typeid(const int &).name() << std::endl;
    // 上面三个的typeid相同的
    auto a = my_traits::is_same<int, my_traits::remove_reference_t<int &>>::value;
    auto b = my_traits::is_same_v<int, my_traits::remove_reference_t<int &>>;
    auto c = my_traits::is_same_v<const int, my_traits::remove_reference_t<const int &>>;
    assert(a);
    assert(b);
    assert(c);
}

void test_remove_cv() {
    std::cout << __FUNCTION__ << std::endl;
    auto a = my_traits::is_same_v<int, my_traits::remove_cv_t< volatile const int>>;
    auto b = my_traits::is_same_v<int, my_traits::remove_cv_t< const volatile int>>;
    auto c = my_traits::is_same_v<const int, my_traits::remove_volatile_t< const volatile int>>;
    auto d = my_traits::is_same_v<const int, my_traits::remove_volatile_t<volatile const int>>;
    auto e = my_traits::is_same_v<volatile int, my_traits::remove_const_t< const volatile int>>;
    auto f = my_traits::is_same_v<volatile int, my_traits::remove_const_t<volatile const int>>;
    assert(a);
    assert(b);
    assert(c);
    assert(d);
    assert(e);
    assert(f);
}

void test_decay() {
    std::cout << __FUNCTION__ << std::endl;
    auto a = my_traits::is_same_v<int, my_traits::decay_t<volatile const int &>>;
    auto b = my_traits::is_same_v<int, my_traits::decay_t<volatile const int>>;
    auto c = my_traits::is_same_v<int, my_traits::decay_t<const int>>;
    auto d = my_traits::is_same_v<int, my_traits::decay_t<volatile int>>;
    auto e = my_traits::is_same_v<int, my_traits::decay_t<int>>;
    assert(a);
    assert(b);
    assert(c);
    assert(d);
    assert(e);
}

int main() {
    test_is_same();
    test_remove_reference();
    test_remove_const();
    test_remove_cv();
    test_decay();

    return 0;
}
