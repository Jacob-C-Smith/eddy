#pragma once

#include <iostream>

#include <compositor.hpp>

class NullCompositor : public Compositor 
{
    public: void Compose() override { std::cout << __FUNCTION__ << "()" << std::endl; };
};