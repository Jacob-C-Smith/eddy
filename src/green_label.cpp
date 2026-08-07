#include <green_label.hpp>

void GreenLabel::Draw ( Window *w )
{
    Rect b = this->Bounds();

    w->DrawLabel
    (
        b.Origin().X(), 
        b.Origin().Y(),
        b.Width(),
        b.Height(),
        "green"
    );

    Composition::Draw(w);
}