#include <sstream>
#include <iomanip>

template <typename T>
std::string to_hex(T x) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << std::right << x;
    return ss.str();
}