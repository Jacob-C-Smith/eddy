#pragma once

#include <window_factory.hpp>
#include <sdl_window.hpp>

class SDLWindowFactory : public WindowFactory 
{
    public:
        SDLWindowFactory() : WindowFactory() { };
        static SDLWindowFactory *Instance() { if ( nullptr == uniqueInstance ) uniqueInstance = new SDLWindowFactory(); return uniqueInstance; };

    protected:
        virtual WindowImp *WindowImpFactoryMethod ( std::string s, Window *w ) override { return new SDLWindow(s, w); };

    private:
        inline static SDLWindowFactory *uniqueInstance;
};