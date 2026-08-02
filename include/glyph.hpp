#pragma once

#include <iostream>

#include <rect.hpp>
#include <iterator.hpp>
#include <null_iterator.hpp>

class Window;
class Composition;

class Glyph 
{
    public:
        virtual void Draw(Window *)            { std::cerr << "Error: Unsupported operation in call to \"" << __PRETTY_FUNCTION__ << "\"" << std::endl; };
        
        Window *GetWindow ( ) { if (_window) return _window; if (_parent) return _parent->GetWindow(); return nullptr; };
        virtual void Position ( Point c ) 
        {
            Rect b = this->Bounds();
            this->Bounds(
                Rect(
                    c.X(),
                    c.Y(),
                    b.Width(),
                    b.Height()
                )
            );
        };
        virtual Point Position ( ) { return Point(); };

        virtual void         Compose        ( )                { };
        virtual void         Size           ( Window *window ) { (void)window; };
        virtual Rect         Bounds         ( )                { return this->_bounds; }
        Glyph               *Parent         ( )                { return this->_parent; };
        virtual Composition *GetComposition ( )                { return _parent ? _parent->GetComposition() : nullptr; }
        virtual bool         Intersects     ( const Point &p ) { return this->Bounds().Contains(p); };
        virtual void         Parent         ( Glyph *parent )  { this->_parent = parent; }
        virtual void         SetWindow      ( Window *window ) { this->_window = window; };
        virtual void         Bounds         ( Rect bounds )    { this->_bounds = bounds; };
        
        virtual Point Cursor ( )                            { std::cerr << "Error: Unsupported operation in call to \"" << __PRETTY_FUNCTION__ << "\"" << std::endl; return Point(); };
        virtual Point Adjust ( Glyph *child, Point cursor ) { (void)child; (void)cursor; std::cerr << "Error: Unsupported operation in call to \"" << __PRETTY_FUNCTION__ << "\"" << std::endl; return Point(); };
        virtual void  Adjust ( Point cursor )               { (void)cursor; std::cerr << "Error: Unsupported operation in call to \"" << __PRETTY_FUNCTION__ << "\"" << std::endl; };
        virtual void Insert(Glyph *, int)                   { std::cerr << "Error: Unsupported operation in call to \"" << __PRETTY_FUNCTION__ << "\"" << std::endl; }
        virtual void Remove(Glyph *)                        { std::cerr << "Error: Unsupported operation in call to \"" << __PRETTY_FUNCTION__ << "\"" << std::endl; }
        virtual Glyph *Child(int)                           { std::cerr << "Error: Unsupported operation in call to \"" << __PRETTY_FUNCTION__ << "\"" << std::endl; return nullptr; }

        virtual Iterator<Glyph*> *CreateIterator() { return new NullIterator<Glyph*>(); }
    protected:
        Glyph(){};
        Glyph *_parent = nullptr;
        Window *_window = nullptr;
        Rect _bounds = {0,0,0,0};
};