#pragma once

#include <point.hpp>
#include <composition.hpp>

class Column : public Composition
{
    public:
        Column() { Composition(); }
        template <typename... Args> Column ( Args... args ) { Composition(); ((this->Insert(args,0)),...); };
        Point Adjust(Glyph *child, Point c) override 
        { 
            return Point
            (
                c.X(),
                c.Y() + child->Bounds().Height()
            );
        };
};