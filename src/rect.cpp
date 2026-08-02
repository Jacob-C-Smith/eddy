#include <rect.hpp>

Rect::Rect(Coord x, Coord y, Coord w, Coord h)
{
    _origin = Point(x, y);
    _extent = Point(w, h);
}

Rect::Rect(const Point &origin, const Point &extent)
{
    _origin = origin;
    _extent = extent;
}

Coord Rect::Width() const 
{
    return _extent.X();
}

void Rect::Width(Coord w) 
{
    _extent.X(w);
}

Coord Rect::Height() const 
{
    return _extent.Y();
}

void Rect::Height(Coord h)
{
    _extent.Y(h);
}

Point &Rect::Origin() const 
{
    return _origin;
}

void Rect::Origin(const Point &p)
{
    _origin = p;
}

Point &Rect::Extent() const
{
    return _extent;
}

void Rect::Extent(const Point &p)
{
    _extent = p;
}

void Rect::MoveTo(const Point &p)
{
    _origin = p;
}

void Rect::MoveBy(const Point &p)
{
    _origin += p;
}

bool Rect::IsEmpty() const
{
    return (_extent.X() == 0) && (_extent.Y() == 0);
}

bool Rect::Contains(const Point &p) const
{
    return 
        (_origin.X() < p.X() && _origin.Y() < p.Y()) &&
        (_origin.X() + _extent.X() > p.X() && _origin.Y() + _extent.Y() > p.Y() );
}