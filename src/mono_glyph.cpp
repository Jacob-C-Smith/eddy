#include "composition.hpp"
#include <mono_glyph.hpp>

MonoGlyph::MonoGlyph ( Glyph *g ) 
{
    Composition::Insert(g, 0);
}

void MonoGlyph::Position ( Point p )
{
    Composition::Child(0)->Position(p);

    Composition::Position(p);
}

void MonoGlyph::Compose ( )
{
    Composition::Compose();
}

void MonoGlyph::Size ( Window *w )
{
    _contents.Get(0)->Size(w);

    Composition::Size(w);
}

void MonoGlyph::Adjust ( Point p )
{
    _contents.Get(0)->Adjust(p);

    Composition::Adjust(p);
}

Point MonoGlyph::Adjust ( Glyph *g, Point c )
{
    return _contents.Get(0)->Adjust(g, c);
}

void MonoGlyph::Insert ( Glyph *g, int i ) 
{
    _contents.Get(0)->Insert(g, i); 
}

void MonoGlyph::Remove ( Glyph *g ) 
{ 
    _contents.Get(0)->Remove(g);
}

Glyph *MonoGlyph::Child ( int i )
{
    return _contents.Get(0)->Child(i);
}

Composition *MonoGlyph::GetComposition ( ) 
{
    return _contents.Get(0)->GetComposition();
}
