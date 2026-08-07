#include <green_button.hpp>

void GreenButton::Draw ( Window *w )
{
    Rect b = this->Bounds();

    w->DrawButton
    (
        b.Origin().X(), 
        b.Origin().Y(),
        b.Width(),
        b.Height(),
        "green"
    );

    Composition::Draw(w);
}