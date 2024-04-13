#include "Soul.h"
#include<QDebug>

Soul::Soul()
{
    pixmap=QPixmap(":/image/image/soul.png");
    this->setPixmap(pixmap);
    vsoul=new QVector2D(0,0);
    vup=vleft=vdown=vright=0;
}

Soul::~Soul()
{
    delete vsoul;
}

void Soul::setv()
{
    this->vsoul->setX(this->vright-this->vleft);
    this->vsoul->setY(this->vdown-this->vup);
}

void Soul::updatePos()
{
    if(!blue_mode)this->setPos(this->x()+vsoul->x(),this->y()+vsoul->y());
}

void Soul::hurt()
{
    qDebug()<<"i am hurt!";
}
