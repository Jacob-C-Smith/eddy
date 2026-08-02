#pragma once

#include <glyph.hpp>
#include <mono_glyph.hpp>

class Scroller : public MonoGlyph
{
    public:
        Scroller( Glyph *g, int w ) : MonoGlyph(g) { _w = w; Compose(); };
        Rect Bounds ( ) override;
        void Draw ( Window * ) override;
    private:
        int _w;
        void DrawScroller ( Window * );
};