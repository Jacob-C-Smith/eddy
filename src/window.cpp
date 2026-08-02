#include <window.hpp>
#include <glyph.hpp>

void Window::SetContents(Glyph *g)
{
    _contents = g; _contents->SetWindow(this);
}