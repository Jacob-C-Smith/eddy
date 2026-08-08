#pragma once
#include <window.hpp>

class ApplicationWindow : public Window 
{
    public: 
        ApplicationWindow(std::string title) : Window(title) { }
};