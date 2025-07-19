#include "Vec2D.hpp"

std::string Vec2D::toString() const {
    return "{"+std::to_string(x)+","+std::to_string(y)+"}";
}

std::string Vec2D::toStringPolarDegree() const {
    return "{"+std::to_string(Norm2())+","+std::to_string(std::atan2(y,x)/M_PI*180.0)+"}";
}
