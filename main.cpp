#include <iostream>

#include <list.hpp>
#include <iterator.hpp>
#include <list_iterator.hpp>

#include <window.hpp>
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
#include <application_window.hpp>

int main ( int argc, const char *argv[] )
{
    (void)argc;
    (void)argv;

    Window *w = new ApplicationWindow("eddy");
    GUIFactory *f = GUIFactory::Instance();
    Glyph *l = f->CreateLabel();
    Glyph *b = f->CreateButton();
    l->Insert(new Row{std::string{"pq"}}, 0);
    b->Insert(new Row{std::string{"PQ"}}, 0);
    
    Glyph *root = new Column(
        new Border(
            new Scroller(
                new Column(
                    new Row(
                        new Character('a'),
                        new Rectangle(Rect(0,0,50,100)),
                        new Column(
                            new Character('X'),
                            l,
                            new Character('Z')
                        ),
                        new Character('b')
                    ),
                    new Row(
                        new Character('x'),
                        new Rectangle(Rect(0,0,100,50)),
                        new Character('y')
                    ),
                    b
                ),
            32),
        8)
    );

    w->SetContents(root);
    w->Redraw();

    return 0;
}