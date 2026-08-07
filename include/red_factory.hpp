#pragma once

#include <gui_factory.hpp>
#include <red_button.hpp>
#include <red_label.hpp>

class RedFactory : public GUIFactory 
{
    public:
        RedFactory() : GUIFactory() { };
        static RedFactory *Instance() { if ( nullptr == uniqueInstance ) uniqueInstance = new RedFactory(); return uniqueInstance; };

    protected:
        virtual Button *ButtonFactoryMethod ( ) override { return new RedButton(); };
        virtual Label *LabelFactoryMethod ( ) override { return new RedLabel(); };

    private:
        inline static RedFactory *uniqueInstance;
};