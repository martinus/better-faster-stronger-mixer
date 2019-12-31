#pragma once

// rotate left
template <typename T>
T rotl(T x, int k) {
    return (x << k) | (x >> (8 * sizeof(T) - k));
}

// rotate right
template <typename T>
T rotr(T x, int k) {
    return (x >> k) | (x << (8 * sizeof(T) - k));
}
