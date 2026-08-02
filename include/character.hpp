#pragma once

#include <window.hpp>
#include <glyph.hpp>

class Character : public Glyph
{
    public:
        Character(char c) : _c(c) { };
        void Draw(Window *) override;
        void Size(Window *) override;
    private:
        char _c;
};