#include <red_label.hpp>

void RedLabel::Draw ( Window *w )
{
    Rect b = this->Bounds();

    w->DrawLabel
    (
        b.Origin().X(), 
        b.Origin().Y(),
        b.Width(),
        b.Height(),
        "red"
    );

    Composition::Draw(w);
}