#pragma once

namespace my_traits {

template <bool v>
struct bool_constant {
    static constexpr bool value = v;
};
using false_type = bool_constant<false>;
using true_type = bool_constant<true>;


template <typename T, typename U>
struct is_same : false_type{};
template <typename T>
struct is_same<T, T> : true_type {
};
template <typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

template <typename T>
struct remove_reference {
    using type = T;
};
template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
struct remove_const {
    using type = T;
};
template <typename T>
struct remove_const<const T> {
    using type = T;
};
template <typename T>
using remove_const_t = typename remove_const<T>::type;

} // namespace my_traits
