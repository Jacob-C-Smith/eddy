#pragma once

#include <list.hpp>
#include <list_iterator.hpp>
#include <window.hpp>
#include <glyph.hpp>

#include <compositor.hpp>
#include <simple_compositor.hpp>

class Composition : public Glyph
{
    public:
        Composition() { _compositor = new SimpleCompositor(); _compositor->SetComposition(this); };
        void              Draw           ( Window * )              override;
        void              SetWindow      ( Window *window )        override;
        void              Insert         ( Glyph *, int )          override;
        Composition      *GetComposition ( )                       override;
        void              Compose        ( )                       override;
        void              Position       ( Point c )               override;
        Point             Position       ( )                       override;
        Point             Adjust         ( Glyph *child, Point c ) override;
        void              Adjust         ( Point c )               override;
        Point             Cursor         ( )                       override;
        void              Size           ( Window *window )        override;
        Rect              Bounds         ( )                       override;
        Iterator<Glyph*> *CreateIterator ( )                       override; 
    private:
        List<Glyph *>  _contents{};
        Rect           _size     = { 0,0,0,0 };
        Point          _position = { 0,0 };
        Compositor    *_compositor = nullptr;
};