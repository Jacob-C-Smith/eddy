#pragma once

#include <button.hpp>
#include <label.hpp>

class GUIFactory 
{
    public:
        static GUIFactory *Instance();
        Button *CreateButton ( ) { return ButtonFactoryMethod(); };
        Label *CreateLabel ( ) { return LabelFactoryMethod(); };

    protected:
        GUIFactory(){};
        virtual Button *ButtonFactoryMethod() = 0;
        virtual Label *LabelFactoryMethod() = 0;

    private:
        inline static GUIFactory *uniqueInstance;
};