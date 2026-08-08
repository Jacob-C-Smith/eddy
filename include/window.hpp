#pragma once

#include <string>

#include <window_imp.hpp>

class Glyph;

class Window 
{
    public:
        Window(std::string title);
        virtual ~Window() = default;
        virtual void Draw();
        virtual void Redraw()    { return _imp->Redraw(); };
        virtual void Raise()     { return _imp->Raise(); }
        virtual void Lower()     { return _imp->Lower(); }
        virtual void Iconify()   { return _imp->Iconify(); }
        virtual void Deiconify() { return _imp->Deiconify(); };
        
        virtual void SetContents(Glyph *);

        virtual void DrawChar   ( char c, int x, int y )                          { return _imp->DrawChar(c, x, y); };
        virtual void DrawRect   ( int x, int y, int w, int h )                    { return _imp->DrawRect(x, y, w, h); };
        virtual void FillRect   ( int x, int y, int w, int h )                    { return _imp->FillRect(x, y, w, h); };
        virtual void DrawButton ( int x, int y, int w, int h, std::string color ) { return _imp->DrawButton(x, y, w, h, color); };
        virtual void DrawLabel  ( int x, int y, int w, int h, std::string color ) { return _imp->DrawLabel(x, y, w, h, color); };
        virtual int  CharWidth  ( char c ) { return _imp->CharWidth(c); };
        virtual int  CharHeight ( char c ) { return _imp->CharHeight(c); };

    protected:
        std::string _title;
        WindowImp *_imp;
        Glyph *_contents;
};