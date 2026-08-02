#include <point.hpp>

Point::Point(Coord x, Coord y)
{
    this->_x = x;
    this->_y = y;
}

Coord Point::X() const { return _x; }
Coord Point::Y() const { return _y; }
void Point::X(Coord x) { _x = x; }
void Point::Y(Coord y) { _y = y; }

Point operator+(const Point &a, const Point &b)
{
    return Point(a.X() + b.X(), a.Y() + b.Y());
}

Point operator-(const Point &a, const Point &b)
{
    return Point(a.X() - b.X(), a.Y() - b.Y());
}

Point operator*(const Point &a, const Point &b)
{
    return Point(a.X() * b.X(), a.Y() * b.Y());
}

Point operator/(const Point &a, const Point &b)
{
    return Point(a.X() / b.X(), a.Y() / b.Y());
}

Point &Point::operator+=(const Point &p)
{
    this->_x += p.X();
    this->_y += p.Y();
    return *this;
}

Point &Point::operator-=(const Point &p)
{
    this->_x -= p.X();
    this->_y -= p.Y();
    return *this;
}

Point &Point::operator*=(const Point &p)
{
    this->_x *= p.X();
    this->_y *= p.Y();
    return *this;
}

Point &Point::operator/=(const Point &p)
{
    this->_x /= p.X();
    this->_y /= p.Y();
    return *this;
}

Point Point::operator-()
{
    return Point(-this->X(), -this->Y());
}

bool operator==(const Point &a, const Point &b)
{
    return (a.X() == b.X() && a.Y() == b.Y());
}

bool operator!=(const Point &a, const Point &b)
{
    return (a.X() != b.X() || a.Y() != b.Y());
}

std::ostream &operator<<(std::ostream &o, const Point&p)
{
    return o << "(" << p._x << ", " << p._y << ")";
}
