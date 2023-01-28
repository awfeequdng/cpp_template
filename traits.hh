#pragma once

namespace type_traits {

template <bool v>
struct bool_constant {
    constexpr static bool value = v;
};
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template <typename T>
struct type_is {
    using type = T;
};

template <typename T, typename U>
struct is_same : false_type{};
template <typename T>
struct is_same<T, T> : true_type {};
template <typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

// remove reference
template <typename T>
struct remove_reference : type_is<T> {};
template <typename T>
struct remove_reference<T &> : type_is<T> {};
template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

// remove const
template <typename T>
struct remove_const : type_is<T> {};
template <typename T>
struct remove_const<const T> : type_is<T> {};
template<typename T>
using remove_const_t = typename remove_const<T>::type;

// remove volatile
template <typename T>
struct remove_volatile : type_is<T> {};
template <typename T>
struct remove_volatile<volatile T> : type_is<T> {};
template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
using decay_t = remove_volatile_t<remove_const_t<remove_reference_t<T>>>;

} // type_traits
