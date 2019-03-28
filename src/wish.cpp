#include "wish.h"

Wish::Wish(PaintedWidget *parent) : PaintedWidget(parent)
{
    addAction("—");
    addAction("X");
    setOnHoverVec();
    setWidth(600);
    setFixedSize(600, 300);
    setStyleSheet("background-color: #414B66");
}

Wish::~Wish()
{

}
