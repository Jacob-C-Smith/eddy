#include <blue_label.hpp>

void BlueLabel::Draw ( Window *w )
{
    Rect b = this->Bounds();

    w->DrawLabel
    (
        b.Origin().X(), 
        b.Origin().Y(),
        b.Width(),
        b.Height(),
        "blue"
    );

    Composition::Draw(w);
}