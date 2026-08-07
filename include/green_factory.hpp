#pragma once

#include <gui_factory.hpp>
#include <green_button.hpp>
#include <green_label.hpp>

class GreenFactory : public GUIFactory 
{
    public:
        GreenFactory() : GUIFactory() { };
        static GreenFactory *Instance() { if ( nullptr == uniqueInstance ) uniqueInstance = new GreenFactory(); return uniqueInstance; };

    protected:
        virtual Button *ButtonFactoryMethod ( ) override { return new GreenButton(); };
        virtual Label *LabelFactoryMethod ( ) override { return new GreenLabel(); };

    private:
        inline static GreenFactory *uniqueInstance;
};