#include <gui_factory.hpp>
#include <red_factory.hpp>
#include <green_factory.hpp>
#include <blue_factory.hpp>
#include <cstdlib>
#include <string>

GUIFactory *GUIFactory::Instance()
{

    if ( nullptr == GUIFactory::uniqueInstance )
    {
        char* env_var = std::getenv("EddyWidget");
        std::string lnf = env_var ? env_var : "";

        if ( lnf == "red" )
            GUIFactory::uniqueInstance = RedFactory::Instance();
        else if ( lnf == "green" )
            GUIFactory::uniqueInstance = GreenFactory::Instance();
        else 
            GUIFactory::uniqueInstance = BlueFactory::Instance();
    }
    
    return GUIFactory::uniqueInstance;
}
