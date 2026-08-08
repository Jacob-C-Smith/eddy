#include "SDL3_ttf/SDL_ttf.h"
#include <sdl_window.hpp>

#include <glyph.hpp>
#include <unistd.h>

SDLWindow::SDLWindow (std::string title, Window *w) 
{

    _title = title;
    _w = w;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(title.c_str(), 800, 720, SDL_WINDOW_HIGH_PIXEL_DENSITY, &this->w, &this->r);

    TTF_Init();
    
    f = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 60.0f);
}

void SDLWindow::Redraw() 
{
    bool done = false;
    

    while (!done) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) done = (event.type == SDL_EVENT_QUIT);

        SDL_SetRenderDrawColor(this->r,255,255,255,255);
        SDL_RenderClear(this->r);
        
        SDL_SetRenderDrawColor(this->r,0,0,0,255);
        _w->Draw();

        SDL_RenderPresent(this->r);

        // usleep(300);
    }
}

void SDLWindow::Raise(){}
void SDLWindow::Lower(){}
void SDLWindow::Iconify(){}
void SDLWindow::Deiconify(){}

void SDLWindow::SetContents() { }

void SDLWindow::DrawChar(char c,int x,int y)
{

    SDL_Surface *t = TTF_RenderText_Blended(f, std::string{c}.c_str(), 1,SDL_Color{0,0,0,255});
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

void SDLWindow::FillRect(int x,int y,int w,int h)
{
    SDL_FRect r{(float)x,(float)y,(float)w,(float)h};
    
    SDL_RenderFillRect(this->r, &r);
    
    return;
}

void SDLWindow::DrawLabel(int x,int y,int w,int h,std::string c)
{
    SDL_FRect r{(float)x,(float)y,(float)w,(float)h};
    SDL_Color lc{};
    
    SDL_GetRenderDrawColor(this->r,&lc.r,&lc.g,&lc.b,&lc.a);

    if ( "red" == c )
        SDL_SetRenderDrawColor(this->r,255,0,0,255);
    else if ( "green" == c )
        SDL_SetRenderDrawColor(this->r,0,255,0,255);
    else
        SDL_SetRenderDrawColor(this->r,0,0,255,255);

    SDL_RenderRect(this->r, &r);
    
    SDL_SetRenderDrawColor(this->r,lc.r,lc.g,lc.b,lc.a);
}

void SDLWindow::DrawButton(int x,int y,int w,int h,std::string c)
{
    SDL_FRect r{(float)x,(float)y,(float)w,(float)h};
    SDL_Color lc{};
    
    SDL_GetRenderDrawColor(this->r,&lc.r,&lc.g,&lc.b,&lc.a);

    if ( "red" == c )
        SDL_SetRenderDrawColor(this->r,255,0,0,255);
    else if ( "green" == c )
        SDL_SetRenderDrawColor(this->r,0,255,0,255);
    else
        SDL_SetRenderDrawColor(this->r,0,0,255,255);

    SDL_RenderFillRect(this->r, &r);
    
    SDL_SetRenderDrawColor(this->r,lc.r,lc.g,lc.b,lc.a);
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