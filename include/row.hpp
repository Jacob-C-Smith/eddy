#pragma once

#include <point.hpp>
#include <composition.hpp>

class Row : public Composition
{
    public:
        Row ( )  { Composition(); }
        Point Adjust ( Glyph *child, Point c ) override 
        { 
            return Point
            (
                c.X() + child->Bounds().Width(),
                c.Y()
            );
        };
};