#pragma once

#include <point.hpp>
#include <composition.hpp>

class MonoGlyph : public Composition
{
    public:
        MonoGlyph( Glyph *g );
        virtual void   Position ( Point )          override;
        virtual void   Compose  ( )                override;
        virtual void   Size     ( Window * )       override;
        virtual void   Adjust   ( Point )          override;
        virtual Point  Adjust   ( Glyph *, Point ) override;
        virtual void   Insert   ( Glyph *, int )   override;
        virtual void   Remove   ( Glyph * )        override;
        virtual Glyph *Child    ( int )            override;
        
        virtual Composition *GetComposition ( ) override;
};