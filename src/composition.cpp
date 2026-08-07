#include <composition.hpp>

void Composition::SetWindow ( Window *window ) 
{
    Glyph::SetWindow(window); 
    Compose();
};


void Composition::Insert(Glyph *g, int i)
{
    (void)i;
    g->Parent(this);
    _contents.Append(g);
    _compositor->Compose();
}

Glyph *Composition::Child ( int i )
{
    return _contents.Get(i);
}

void Composition::Draw(Window *w)
{
    
    Iterator<Glyph *> *it = CreateIterator();
    
    for(it->First(); !it->IsDone(); it->Next())
        it->CurrentItem()->Draw(w);

    delete it;
}

Rect Composition::Bounds ( )
{
    if ( 0 == _contents.Count() )
    {
        return Glyph::Bounds();
    }

    float minX = 100000, minY = 100000, maxX = -100000, maxY = -100000;

    
    Iterator<Glyph *> *it = CreateIterator();
    
    for(it->First(); !it->IsDone(); it->Next())
    {
        Rect b = it->CurrentItem()->Bounds();

        minX = (minX < b.Origin().X()) ? minX : b.Origin().X();
        minY = (minY < b.Origin().Y()) ? minY : b.Origin().Y();
        maxX = (maxX > b.Origin().X() + b.Width()) ? maxX : b.Origin().X() + b.Width();
        maxY = (maxY > b.Origin().Y() + b.Height()) ? maxY : b.Origin().Y() + b.Height();
    }

    delete it;

    return Rect{minX,minY,maxX-minX,maxY-minY};
}

Composition *Composition::GetComposition ( ) { return this; };
void Composition::Compose ( ) { _compositor->Compose(); };
void Composition::Position ( Point c ) { _position = c; };
Point Composition::Position ( ) { return _position; };
Point Composition::Adjust ( Glyph *child, Point c ) 
{ 
    return Point
    (
        c.X() + child->Bounds().Width(),
        c.Y()
    ); 
};
void Composition::Adjust ( Point c ) 
{
    _size = Rect
    (
        0,
        0,
        c.X() - _position.X(),
        c.Y() - _position.Y()
    );
};

Point Composition::Cursor ( ) { return _position; };

void Composition::Size ( Window * ) 
{ 
    Glyph::Bounds
    (
        Rect
        (
            _position.X(), 
            _position.Y(),
            _size.Width(),
            _size.Height()
        )
    );
};

Iterator<Glyph*> *Composition::CreateIterator() { return new ListIterator<Glyph*>(&_contents); }