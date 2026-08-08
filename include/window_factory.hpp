#pragma once

#include <window_imp.hpp>

class Window;

class WindowFactory 
{
    public:
        static WindowFactory *Instance();
        WindowImp *CreateWindowImp (std::string title, Window *w) { return WindowImpFactoryMethod(title, w); };

    protected:
        WindowFactory(){};
        virtual WindowImp *WindowImpFactoryMethod(std::string, Window *) = 0;

    private:
        inline static WindowFactory *uniqueInstance;
};