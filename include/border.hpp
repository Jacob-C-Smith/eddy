#pragma once

#include <glyph.hpp>
#include <mono_glyph.hpp>

class Border : public MonoGlyph
{
    public:
        Border( Glyph *g, int s ) : MonoGlyph(g) { _s = s; Compose(); };
        void Position ( Point ) override;
        Rect Bounds ( ) override;
        void Draw ( Window * ) override;
    private:
        int _s;
        void DrawBorder ( Window * );
};