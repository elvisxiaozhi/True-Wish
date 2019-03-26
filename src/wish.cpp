#include "wish.h"

Wish::Wish(PaintedWidget *parent) : PaintedWidget(parent)
{
    setWidth(1000);
    closeAction = addAction("X");
    setStyleSheet("background-color: #414B66");
}

Wish::~Wish()
{

}
