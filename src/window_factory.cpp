#include "sdl_window_factory.hpp"
#include <gui_factory.hpp>
#include <red_factory.hpp>
#include <green_factory.hpp>
#include <blue_factory.hpp>
#include <cstdlib>
#include <string>

WindowFactory *WindowFactory::Instance()
{

    if ( nullptr == WindowFactory::uniqueInstance )
    {
        char* env_var = std::getenv("EddyWindow");
        std::string win = env_var ? env_var : "";

        WindowFactory::uniqueInstance = SDLWindowFactory::Instance();
    }
    
    return WindowFactory::uniqueInstance;
}
