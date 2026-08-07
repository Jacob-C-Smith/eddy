#pragma once

#include <mono_glyph.hpp>
#include <row.hpp>

class Label : public MonoGlyph
{
    public:
        Label() : MonoGlyph(new Row()) { };
};