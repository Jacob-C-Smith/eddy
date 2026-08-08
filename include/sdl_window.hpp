#pragma once
#include <window_imp.hpp>
#include <window.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

class Glyph;

class SDLWindow : public WindowImp
{
    public:
        SDLWindow(std::string title, Window *w);
        ~SDLWindow();
        void Redraw();
        void Raise();
        void Lower();
        void Iconify();
        void Deiconify();
        
        void SetContents(void);
        void DrawChar(char,int,int);
        void DrawRect(int,int,int,int);
        void FillRect(int,int,int,int);
        void DrawButton(int,int,int,int,std::string);
        void DrawLabel(int,int,int,int,std::string);
        int CharWidth(char);
        int CharHeight(char);

    private:
        std::string _title;
        Window *_w;
        SDL_Window *w;
        SDL_Renderer *r;
        TTF_Font *f;
};