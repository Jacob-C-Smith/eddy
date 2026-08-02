#pragma once 
#include <point.hpp>

class Rect
{
    public:
        static const Point Zero;

        Rect(Coord x, Coord y, Coord w, Coord h);
        Rect(const Point &origin, const Point &extent);

        Coord Width() const; void Width(Coord);
        Coord Height() const; void Height(Coord);
        Coord Left() const; void Left(Coord);
        Coord Bottom() const; void Bottom(Coord);
        
        Point &Origin() const; void Origin(const Point&);
        Point &Extent() const; void Extent(const Point&);

        void MoveTo(const Point &);
        void MoveBy(const Point &);

        bool IsEmpty() const;
        bool Contains(const Point &) const;

    private:
        mutable Point _origin;
        mutable Point _extent;
};