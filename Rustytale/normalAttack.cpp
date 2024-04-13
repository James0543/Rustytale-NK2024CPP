#include "normalAttack.h"

normalAttack::normalAttack(QObject *parent) : QObject(parent)
{

}

normalAttack::normalAttack(int x,int y,int width,int height,Soul* soul)
{
    this->setRect(x,y,width,height);
    this->soulptr=soul;
    this->setBrush(Qt::white);

    update_timer=new QTimer;
    move_timer_x= new QTimer;
    move_timer_y= new QTimer;
    update_timer->start();
    update_timer->setInterval(100);
    connect(update_timer,&QTimer::timeout,this,[=]()
    {
        if(this->collidesWithItem(soulptr)) collide_with_soul=true;
        else collide_with_soul=false;

        if(collide_with_soul) soul->hurt();
    });
}

void normalAttack::attackMove(int tx,int ty)
{
    move_timer_x->setInterval(tx);
    move_timer_y->setInterval(ty);
    move_timer_x->start();
    move_timer_y->start();
    connect(move_timer_x,&QTimer::timeout,this,[=]()
    {
        this->setPos(this->x()+1,this->y());
    });
    connect(move_timer_y,&QTimer::timeout,this,[=]()
    {
        this->setPos(this->x(),this->y()+1);
    });
}
