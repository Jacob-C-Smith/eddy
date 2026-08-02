#include <border.hpp>

void Border::Position ( Point p )
{
    MonoGlyph::Position(
        Point(
            p.X() + _s,
            p.Y() + _s
        )
    );
}

Rect Border::Bounds( )
{
    Rect cb = MonoGlyph::Bounds();

    return Rect
    (
        cb.Origin().X() - _s,
        cb.Origin().Y() - _s,
        cb.Width() + 2 * _s,
        cb.Height() + 2 * _s
    );
}

void Border::Draw ( Window *w )
{
    MonoGlyph::Draw(w);

    DrawBorder(w);
}

void Border::DrawBorder ( Window *w )
{
    Rect b = Bounds();
    for (int i = 0; i < _s; i++)
        w->DrawRect(b.Origin().X()+i, b.Origin().Y()+i, b.Width()-2*i, b.Height()-2*i);
    
}
