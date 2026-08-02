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
        virtual void              Draw           ( Window * )              override;
        virtual void              SetWindow      ( Window *window )        override;
        virtual void              Insert         ( Glyph *, int )          override;
        virtual Glyph            *Child          ( int )                   override;
        virtual Composition      *GetComposition ( )                       override;
        virtual void              Compose        ( )                       override;
        virtual void              Position       ( Point c )               override;
        virtual Point             Position       ( )                       override;
        virtual Point             Adjust         ( Glyph *child, Point c ) override;
        virtual void              Adjust         ( Point c )               override;
        virtual Point             Cursor         ( )                       override;
        virtual void              Size           ( Window *window )        override;
        virtual Rect              Bounds         ( )                       override;
        virtual Iterator<Glyph*> *CreateIterator ( )                       override; 
    protected:
        List<Glyph *>  _contents{};
        Rect           _size     = { 0,0,0,0 };
        Point          _position = { 0,0 };
        Compositor    *_compositor = nullptr;
};