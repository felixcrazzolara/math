#pragma once

#include <cmath>
#include <string>
#include <utility>

#define square(x) ((x)*(x))

template <class T>
struct Vec2;

using Vec2D = Vec2<double>;

template <class T>
struct Vec2 {

constexpr Vec2(const T &x, const T &y) :
    x{x}, y{y}
{}

template <class U>
Vec2(const Vec2<U> &a) :
    x{static_cast<T>(a.x)}, y{static_cast<T>(a.y)}
{}

inline double Norm2() const {
    return std::sqrt( square(x) + square(y) );
}

inline double Norm2Squared() const {
    return square(x) + square(y);
}

template <class U>
inline double dot(const Vec2<U> &a) const {
    return x*a.x + y*a.y;
}

inline Vec2D to_polar() const {
    const double r   = this->Norm2();
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
inline bool operator ==(const Vec2<U> &a) const {
    return x == a.x && y == a.y;
}

std::string toString() const;

std::string toStringPolarDegree() const;

inline Vec2<T>& round() {
    x = std::round(x);
    y = std::round(y);
    return *this;
}

std::pair<T,T> pair() const {
    return {x,y};
}

T x;
T y;

};

template <typename T, typename U>
inline Vec2<T> operator +(const Vec2<T> &a, const Vec2<U> &b) {
    return Vec2<T>({a.x + b.x, a.y + b.y});
}

inline Vec2D operator -(const Vec2D& a, const Vec2D& b) {
    return Vec2D({a.x-b.x, a.y-b.y});
}

inline Vec2D operator *(const Vec2D& a, const double& b) {
    return Vec2D({a.x*b, a.y*b});
}

inline Vec2D operator *(const double& a, const Vec2D& b) {
    return Vec2D({a*b.x, a*b.y});
}

inline Vec2D operator /(const Vec2D& a, const double& b) {
    return Vec2D({a.x/b, a.y/b});
}

inline Vec2D operator -(const Vec2D& a) {
    return Vec2D{-a.x,-a.y};
}
