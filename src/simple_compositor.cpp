#include <simple_compositor.hpp>
#include <point.hpp>
#include <glyph.hpp>
#include <composition.hpp>

void SimpleCompositor::Compose()
{
    
    Glyph *parent = nullptr;
    Point c = _composition->Cursor();

    Iterator<Glyph *> *it = _composition->CreateIterator();
    
    for(it->First(); !it->IsDone(); it->Next())
    {

        Glyph *child = it->CurrentItem();

        child->Size(_composition->GetWindow());

        child->Position(c);

        child->Compose();

        c = _composition->Adjust(child, c);
    }

    delete it;

    _composition->Adjust(c);

    _composition->Size(_composition->GetWindow());

    parent = _composition->Parent();

    if (parent) parent->Adjust(_composition->Cursor());
}