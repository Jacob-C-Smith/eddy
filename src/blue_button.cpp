#include <blue_button.hpp>

void BlueButton::Draw ( Window *w )
{
    Rect b = this->Bounds();

    w->DrawButton
    (
        b.Origin().X(), 
        b.Origin().Y(),
        b.Width(),
        b.Height(),
        "blue"
    );

    Composition::Draw(w);
}