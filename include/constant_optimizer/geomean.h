#pragma once

#include <cmath>
#include <initializer_list>
#include <vector>

template <typename Iter>
double geomean(Iter begin, Iter end) {
    double logSum = 0.0;
    size_t count = 0;
    while (begin != end) {
        logSum += std::log(*begin);
        ++count;
        ++begin;
    }
    return std::exp(logSum / static_cast<double>(count));
}

inline double geomean(std::initializer_list<double> l) {
    return geomean(l.begin(), l.end());
}

inline double geomean(std::vector<double> const& l) {
    return geomean(l.begin(), l.end());
}