#include <null_window.hpp>

#include <glyph.hpp>

void NullWindow::Redraw() { std::cout << __FUNCTION__ << "()" << std::endl; _contents->Draw(this); }

void NullWindow::Raise()     { std::cout << __FUNCTION__ << "()" << std::endl; }
void NullWindow::Lower()     { std::cout << __FUNCTION__ << "()" << std::endl; }
void NullWindow::Iconify()   { std::cout << __FUNCTION__ << "()" << std::endl; }
void NullWindow::Deiconify() { std::cout << __FUNCTION__ << "()" << std::endl; }

void NullWindow::DrawChar(char c,int x,int y)      { std::cout << __FUNCTION__ << "(" << c << ", " << x << ", " << y << ")" << std::endl; }
void NullWindow::DrawRect(int x,int y,int w,int h) { std::cout << __FUNCTION__ << "(" << x << ", " << y << ", " << w << ", " << h << ")" << std::endl; }
int NullWindow::CharWidth(char c)                  { std::cout << __FUNCTION__ << "(" << c << ")" << std::endl; return 0; }
int NullWindow::CharHeight(char c)                 { std::cout << __FUNCTION__ << "(" << c << ")" << std::endl; return 0; }

NullWindow::~NullWindow(){}