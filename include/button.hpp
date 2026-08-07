#pragma once

#include <mono_glyph.hpp>
#include <row.hpp>

class Button : public MonoGlyph
{
    public:
        Button() : MonoGlyph(new Row()) { };
};