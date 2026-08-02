#pragma once
#include <window.hpp>

class Glyph;

class NullWindow : public Window 
{
    public:
        NullWindow(std::string title){ _title = title; };
        ~NullWindow();
        void Redraw();
        void Raise();
        void Lower();
        void Iconify();
        void Deiconify();
        
        void DrawChar(char,int,int);
        void DrawRect(int,int,int,int);
        int CharWidth(char);
        int CharHeight(char);
};