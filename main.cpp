#include <iostream>

#include <list.hpp>
#include <iterator.hpp>
#include <list_iterator.hpp>

#include <window.hpp>
#include <sdl_window.hpp>
#include <null_window.hpp>
#include <point.hpp>
#include <rect.hpp>
#include <rectangle.hpp>
#include <row.hpp>
#include <column.hpp>
#include <glyph.hpp>
#include <character.hpp>
#include <border.hpp>
#include <scroller.hpp>
#include <gui_factory.hpp>
#include <button.hpp>

int main ( int argc, const char *argv[] )
{
    (void)argc;
    (void)argv;

    Window *w = new SDLWindow("eddy");
    GUIFactory *f = GUIFactory::Instance();

    Glyph *_g[] = 
    {
        new Row(),
            new Column(),
                new Row("composite"),
                new Row("strategy"),
            new Column(),
                new Row("decorator"),
                new Row("glyph"),
                
    };

    Glyph *_b = f->CreateButton();
    Glyph *_l = f->CreateLabel();

    _b->Insert(_g[6], 0);
    _l->Insert(_g[5], 0);

    _g[1]->Insert(_g[2], 0);
    _g[1]->Insert(_g[3], 1);

    _g[4]->Insert(_l, 0);
    _g[4]->Insert(_b, 1);

    _g[0]->Insert(new Scroller(new Border(_g[1],1),32), 0);
    _g[0]->Insert(new Border(_g[4],1), 1);

    Glyph *h = _g[0];
    Glyph *root = new Column();
    root->Insert(h, 0);
    w->SetContents(root);

    w->Redraw();
    
    return 0;
}