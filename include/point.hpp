#pragma once

#include <ostream>
#include <istream>
typedef float Coord;

class Point
{
    public:
        static const Point Zero;

        Point(Coord x = 0.0, Coord y = 0.0);

        Coord X() const; void X(Coord x);
        Coord Y() const; void Y(Coord y);

        friend Point operator+(const Point &, const Point &);
        friend Point operator-(const Point &, const Point &);
        friend Point operator*(const Point &, const Point &);
        friend Point operator/(const Point &, const Point &);

        Point &operator+=(const Point &);
        Point &operator-=(const Point &);
        Point &operator*=(const Point &);
        Point &operator/=(const Point &);
        
        Point operator-();

        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &, const Point&);
        friend std::istream &operator>>(std::istream &, Point&);
    private:
        float _x, _y;
};