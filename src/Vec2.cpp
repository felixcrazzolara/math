#include "Vec2.hpp"

template <class T>
std::string Vec2<T>::to_string_polar_degree() const {
    return "{" + std::to_string(L2()) + "," + std::to_string(std::atan2(y,x)/M_PI*180.0) + "}";
}

