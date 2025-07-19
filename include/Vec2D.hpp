#pragma once

#include <string>
#include <cmath>

#define square(x) ((x)*(x))

struct Vec2D {

inline double Norm2() const {
    return std::sqrt( square(x) + square(y) );
}

inline double Norm2Squared() const {
    return square(x) + square(y);
}

inline double dot(const Vec2D& a) const {
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

inline Vec2D& operator +=(const Vec2D& a) {
    x += a.x;
    y += a.y;
    return *this;
}

inline Vec2D& operator -=(const Vec2D& a) {
    x -= a.x;
    y -= a.y;
    return *this;
}

inline Vec2D& operator /=(const double a) {
    x /= a;
    y /= a;
    return *this;
}

inline bool operator ==(const Vec2D& a) const {
    return x == a.x && y == a.y;
}

std::string toString() const;

std::string toStringPolarDegree() const;

double x;
double y;

};

inline Vec2D operator +(const Vec2D& a, const Vec2D& b) {
    return Vec2D({a.x+b.x, a.y+b.y});
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
