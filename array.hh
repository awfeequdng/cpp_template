#pragma once

#include <type_traits>
template <typename T, int N>
struct Array{

    T operator[](int idx) {
        if (idx < N) {
            return data_[idx];
        }
        throw "index out of range";
    }

    T data_[N];
};
template <typename...Args>
Array(const Args&... args) -> Array<std::common_type_t<Args...>, sizeof...(Args)>;
