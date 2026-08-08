#include "window_factory.hpp"
#include <window.hpp>
#include <glyph.hpp>

Window::Window ( std::string title ) 
{
    this->_imp = WindowFactory::Instance()->CreateWindowImp(title, this);
}

void Window::Draw ( ) 
{
    if ( _contents ) _contents->Draw(this);
}

void Window::SetContents(Glyph *g)
{
    _contents = g;
    _contents->SetWindow(this);
    _imp->SetContents();
}