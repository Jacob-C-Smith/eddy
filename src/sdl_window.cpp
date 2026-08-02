#include "SDL3_ttf/SDL_ttf.h"
#include <sdl_window.hpp>

#include <glyph.hpp>

SDLWindow::SDLWindow (std::string title) 
{

    _title = title;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(title.c_str(), 800, 600, 0, &this->w, &this->r);

    TTF_Init();
    
    f = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 12.0f);
}

void SDLWindow::Redraw() 
{
    bool done = false;
    
    while (!done) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                done = true;
            }
        }

        SDL_SetRenderDrawColor(this->r,255,255,255,255);
        SDL_RenderClear(this->r);
        
        SDL_SetRenderDrawColor(this->r,0,0,0,255);
        _contents->Draw(this);

        SDL_RenderPresent(this->r);
    }
}

void SDLWindow::Raise(){}
void SDLWindow::Lower(){}
void SDLWindow::Iconify(){}
void SDLWindow::Deiconify(){}

void SDLWindow::DrawChar(char c,int x,int y)
{

    SDL_Surface *t = TTF_RenderText_Blended(f, std::string{c}.c_str(), 1,SDL_Color{0,0,0,0});
    SDL_Texture *u = SDL_CreateTextureFromSurface(r, t);
    SDL_FRect dst{(float)x,(float)y,0,0};

    SDL_GetTextureSize(u, &dst.w, &dst.h);

    SDL_RenderTexture(r, u, NULL, &dst);

    SDL_DestroyTexture(u);
    SDL_DestroySurface(t);
}

void SDLWindow::DrawRect(int x,int y,int w,int h)
{
    SDL_FRect r{(float)x,(float)y,(float)w,(float)h};
    
    SDL_RenderRect(this->r, &r);

    return;
}

int SDLWindow::CharWidth(char c)
{
    int width, height;

    TTF_GetStringSize(f, std::string{c}.c_str(), 1, &width, &height);

    return width;
}

int SDLWindow::CharHeight(char c)
{
    int width, height;

    TTF_GetStringSize(f, std::string{c}.c_str(), 1, &width, &height);

    return height;    
}

SDLWindow::~SDLWindow()
{
    TTF_Quit();
    SDL_DestroyRenderer(this->r);
    SDL_DestroyWindow(this->w);
    SDL_Quit();
}