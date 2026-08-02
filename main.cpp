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

int main ( int argc, const char *argv[] )
{
    (void)argc;
    (void)argv;

    Window *w = new SDLWindow("eddy");
    // Window *w = new NullWindow("eddy");

    Glyph *_g[] = 
    {
        new Column(),
            new Row(),
                new Character('a'),
                new Rectangle(Rect(0,0,100,200)),
                new Column(),
                    new Character('X'),
                    new Character('Y'),
                    new Character('Z'),
                new Character('b'),
            new Row("woh-woh-wee-woh"),
    };

    _g[4]->Insert(_g[5], 0);
    _g[4]->Insert(_g[6], 1);
    _g[4]->Insert(_g[7], 2);

    _g[1]->Insert(_g[2], 0);
    _g[1]->Insert(_g[3], 1);
    _g[1]->Insert(_g[4], 2);
    _g[1]->Insert(_g[8], 3);

    _g[0]->Insert(_g[1], 0);
    _g[0]->Insert(_g[9], 0);

    Glyph *h = new Border(new Scroller(new Border(_g[0],1), 32), 1);
    Glyph *root = new Column();
    root->Insert(h, 0);
    w->SetContents(root);

    w->Redraw();
    
    return 0;
}