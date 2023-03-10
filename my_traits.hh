#pragma once

#include <tuple>
// 什么是traits
// 可以认为是：用来提高编译器泛型能力的类或者对象
namespace my_traits {

template <typename...Args>
using void_t = void;

template <bool v>
struct bool_constant {
    static constexpr bool value = v;
};
using false_type = bool_constant<false>;
using true_type = bool_constant<true>;

template <typename T>
struct type_is {
    using type = T;
};

// is same
template <typename T, typename U>
struct is_same : false_type{};
template <typename T>
struct is_same<T, T> : true_type {
};
template <typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

// remove reference
template <typename T>
struct remove_reference : type_is<T>{};
template <typename T>
struct remove_reference<T&> : type_is<T> {};
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

// remove const
template <typename T>
struct remove_const : type_is<T>{
};
template <typename T>
struct remove_const<const T> : type_is<T> {
};
template <typename T>
using remove_const_t = typename remove_const<T>::type;

// remove volatile
template <typename T>
struct remove_volatile : type_is<T>{
};
template <typename T>
struct remove_volatile<volatile T> : type_is<T>{
};
template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
struct remove_cv {
    using type = remove_volatile_t<remove_const_t<T>>;
};
template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

// decay_t
template <typename T>
struct decay {
    using type = remove_cv_t<remove_reference_t<T>>;
};
template <typename T>
using decay_t = typename decay<T>::type;


// count
template <typename...Args>
int count(const Args&... args) {
    // return sizeof...(args);
    return sizeof...(Args);
}

// make_tuple
template <typename...Args>
auto make_tuple(const Args&... args) {
    return std::make_tuple(args...);
}

// tie
template <typename... Args>
std::tuple<Args&...> tie(Args&...args) {
    return {args...};
}

// move
template <typename T>
remove_reference_t<T>&& move(T&& v) {
    return static_cast<remove_reference_t<T>&&>(v);
}

// conditional
template <bool, typename T, typename F>
struct conditional : type_is<T> {};
template <typename T, typename F>
struct conditional<false, T, F> : type_is<F> {};
template <bool b, typename T, typename F>
using conditional_t = typename conditional<b, T, F>::type;

// has x
template <typename, typename>
struct has_x : false_type {};
template <typename T>
struct has_x<T, decltype(T::x)> : true_type {};

// enable if
template <bool, typename T = void>
struct enable_if {};
template <typename T>
struct enable_if<true, T> : type_is<T> {
};
template <bool b, typename T=void>
using enable_if_t = typename enable_if<b, T>::type;

// has member type
template <typename, typename = void_t<>>
struct has_member_type : false_type {};
template <typename T>
struct has_member_type<T, void_t<typename T::type>> : true_type {};
template <typename T, typename V= void_t<>>
constexpr bool has_member_type_v = has_member_type<T>::value;


} // namespace my_traits
