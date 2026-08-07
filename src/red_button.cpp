#include <red_button.hpp>

void RedButton::Draw ( Window *w )
{
    Rect b = this->Bounds();

    w->DrawButton
    (
        b.Origin().X(), 
        b.Origin().Y(),
        b.Width(),
        b.Height(),
        "red"
    );

    Composition::Draw(w);
}