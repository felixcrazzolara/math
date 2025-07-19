#include "Vec2D.hpp"

template <class T>
std::string Vec2<T>::toString() const {
    return "{"+std::to_string(x)+","+std::to_string(y)+"}";
}

template <class T>
std::string Vec2<T>::toStringPolarDegree() const {
    return "{"+std::to_string(Norm2())+","+std::to_string(std::atan2(y,x)/M_PI*180.0)+"}";
}

template <> std::string Vec2D::toString() const;
