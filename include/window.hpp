#pragma once

#include <string>

class Glyph;

class Window 
{
    public:
        virtual ~Window() = default;
        virtual void Redraw() = 0;
        virtual void Raise() = 0;
        virtual void Lower() = 0;
        virtual void Iconify() = 0;
        virtual void Deiconify() = 0;
        
        virtual void SetContents(Glyph *);

        virtual void DrawChar(char,int,int) = 0;
        virtual void DrawRect(int,int,int,int) = 0;
        virtual void FillRect(int,int,int,int) = 0;
        virtual void DrawButton(int,int,int,int,std::string) = 0;
        virtual void DrawLabel(int,int,int,int,std::string) = 0;
        virtual int CharWidth(char) = 0;
        virtual int CharHeight(char) = 0;

    protected:
        Window() = default;
        std::string _title;
        Glyph *_contents;
};