#pragma once
#include <window.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

class Glyph;

class SDLWindow : public Window 
{
    public:
        SDLWindow(std::string title);
        ~SDLWindow();
        void Redraw();
        void Raise();
        void Lower();
        void Iconify();
        void Deiconify();
        
        void DrawChar(char,int,int);
        void DrawRect(int,int,int,int);
        int CharWidth(char);
        int CharHeight(char);

    private:
        SDL_Window *w;
        SDL_Renderer *r;
        TTF_Font *f;
};