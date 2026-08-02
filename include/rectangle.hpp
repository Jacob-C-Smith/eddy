#pragma once

#include <window.hpp>
#include <glyph.hpp>

class Rectangle : public Glyph
{
    public:
        Rectangle(Rect r);
        void Draw(Window *) override;
    private:
        Rect _dimensions;
};