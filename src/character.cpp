#include <iostream>
#include <character.hpp>

void Character::Draw(Window *w)
{ 
    w->DrawChar
    (
        this->_c,
        this->Bounds().Origin().X(),
        this->Bounds().Origin().Y()        
    );
}

void Character::Size(Window *w)
{
    if ( w )
        this->Bounds
        (
            Rect
            (
                0,
                0,
                w->CharWidth(this->_c),
                w->CharHeight(this->_c)
            )
        );
}