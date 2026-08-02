#pragma once

#include <iostream>

#include <compositor.hpp>

class SimpleCompositor : public Compositor 
{
    public: void Compose() override;
};