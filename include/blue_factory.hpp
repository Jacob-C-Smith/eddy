#pragma once

#include <gui_factory.hpp>
#include <blue_button.hpp>
#include <blue_label.hpp>

class BlueFactory : public GUIFactory 
{
    public:
        BlueFactory() : GUIFactory() { };
        static BlueFactory *Instance() { if ( nullptr == uniqueInstance ) uniqueInstance = new BlueFactory(); return uniqueInstance; };

    protected:
        virtual Button *ButtonFactoryMethod ( ) override { return new BlueButton(); };
        virtual Label *LabelFactoryMethod ( ) override { return new BlueLabel(); };

    private:
        inline static BlueFactory *uniqueInstance;
};