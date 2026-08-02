#include <iostream>
#include <rectangle.hpp>

Rectangle::Rectangle(Rect r) : _dimensions(r)
{
    this->Bounds(r);
}

void Rectangle::Draw(Window *w)
{ 
    w->DrawRect
    (
        this->Bounds().Origin().X() + _dimensions.Origin().X(), 
        this->Bounds().Origin().Y() + _dimensions.Origin().Y(), 
        this->_dimensions.Width(), 
        this->_dimensions.Height()
    );
}

