#pragma once

class Composition;

class Compositor 
{
    public:
        void SetComposition(Composition *);
        virtual void Compose() = 0;
    protected:
        Composition *_composition;
};