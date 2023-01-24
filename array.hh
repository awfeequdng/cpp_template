#pragma once

template <typename T, int N>
class Array{
public:
    T operator[](int idx) {
        if (idx < N) {
            return data_[idx];
        }
        throw "index out of range";
    }
private:
    T data_[N];
};