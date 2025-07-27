#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <utility>

#define square(x) ((x)*(x))

template <class T>
requires std::is_arithmetic_v<T>
struct Vec2;

using Vec2D = Vec2<double>;

template <class T>
requires std::is_arithmetic_v<T>
struct Vec2 {

using type = T;

constexpr Vec2(const T &x, const T &y) :
    x{x}, y{y}
{}

template <class U>
Vec2(const Vec2<U> &a) :
    x{a.x}, y{a.y}
{}

inline double L2() const {
    return std::sqrt( square(x) + square(y) );
}

inline double L2_squared() const {
    return square(x) + square(y);
}

template <class U>
inline double dot(const Vec2<U> &a) const {
    return x*a.x + y*a.y;
}

inline Vec2D to_polar() const {
    const double r   = this->L2();
    const double phi = std::atan2(y,x);
    return Vec2D{r,phi};
}

inline Vec2D from_polar() const {
    return Vec2D{x*std::cos(y),x*std::sin(y)};
}

template <class U>
inline Vec2<T>& operator +=(const Vec2<U> &a) {
    x += a.x;
    y += a.y;
    return *this;
}

template <class U>
inline Vec2<T>& operator -=(const Vec2<U> &a) {
    x -= a.x;
    y -= a.y;
    return *this;
}

inline Vec2<T>& operator /=(const double a) {
    x /= a;
    y /= a;
    return *this;
}

template <class U>
requires std::is_arithmetic_v<U>
inline Vec2<std::common_type_t<T, U>> operator +(const U &a) const {
    using R = std::common_type_t<T, U>;
    return Vec2<R>{x + a, y + a};
}

template <class U>
requires std::is_arithmetic_v<U>
inline Vec2<std::common_type_t<T, U>> operator *(const U &b) const {
    using R = std::common_type_t<T, U>;
    return Vec2<R>({x * b, y * b});
}

template <class U>
requires std::is_arithmetic_v<U>
inline Vec2<std::common_type_t<T, U>> operator /(const U &b) const {
    using R = std::common_type_t<T, U>;
    return Vec2<R>({x / b, y / b});
}

template <class U>
inline bool operator ==(const Vec2<U> &a) const {
    return x == a.x && y == a.y;
}

std::string to_string() const {
    return "{" + std::to_string(x) + "," + std::to_string(y) + "}";
}

std::string to_string_polar_degree() const;

inline Vec2<T>& round() {
    x = std::round(x);
    y = std::round(y);
    return *this;
}

std::pair<T,T> pair() const {
    return {x,y};
}

template <typename U>
requires std::is_arithmetic_v<U>
inline Vec2<U> as() const {
    return Vec2<U>{static_cast<U>(x), static_cast<U>(y)};
}

template <typename U, typename K = U::type>
requires std::is_same_v<U, Vec2<K>>
inline Vec2<K> as() const {
    return Vec2<K>{static_cast<K>(x), static_cast<K>(y)};
}

T x;
T y;

};

template <typename T, typename U>
inline Vec2<std::common_type_t<T, U>> operator +(const Vec2<T> &a, const Vec2<U> &b) {
    using R = std::common_type_t<T, U>;
    return Vec2<R>(a.x + b.x, a.y + b.y);
}

template <typename T, typename U>
inline Vec2<std::common_type_t<T, U>> operator -(const Vec2<T> &a, const Vec2<U> &b) {
    using R = std::common_type_t<T, U>;
    return Vec2<R>(a.x - b.x, a.y - b.y);
}

inline Vec2D operator *(const double& a, const Vec2D& b) {
    return Vec2D({a*b.x, a*b.y});
}

inline Vec2D operator -(const Vec2D& a) {
    return Vec2D{-a.x,-a.y};
}

template <typename T>
inline std::ostream& operator <<(std::ostream &out, const Vec2<T> &a) {
    out << a.to_string();
    return out;
}

#undef square
