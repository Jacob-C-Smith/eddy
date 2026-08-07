#pragma once

#include <point.hpp>
#include <composition.hpp>
#include <character.hpp>

class Row : public Composition
{
    public:
        Row ( )  { Composition(); }
        Row ( std::string s ) { Composition(); for(std::string::size_type i = 0; i < s.length(); i++ ) this->Insert(new Character(s[i]),i); };
        Point Adjust ( Glyph *child, Point c ) override 
        { 
            return Point
            (
                c.X() + child->Bounds().Width(),
                c.Y()
            );
        };
};