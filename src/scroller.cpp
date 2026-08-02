#include <scroller.hpp>

Rect Scroller::Bounds( )
{
    Rect cb = MonoGlyph::Bounds();

    return Rect
    (
        cb.Origin().X(),
        cb.Origin().Y(),
        cb.Width() + _w,
        cb.Height()
    );
}

void Scroller::Draw ( Window *w )
{
    MonoGlyph::Draw(w);

    DrawScroller(w);
}

void Scroller::DrawScroller ( Window *w )
{
    Rect b = Bounds();
    w->DrawRect
    (
        b.Origin().X() + b.Width() - _w,
        b.Origin().Y(),
        _w,
        b.Height()
    );
    w->FillRect
    (
        b.Origin().X()+b.Width() - _w + (_w >> 2),
        b.Origin().Y() + (_w >> 2),
        _w - (_w >> 1),
        b.Height() - (_w >> 1)
    );
}
