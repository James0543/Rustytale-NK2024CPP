#include "Sword.h"

Sword::Sword(Soul *soul,QGraphicsScene *background)
{
    QPixmap pixmap=QPixmap(":/image/image/sword.png");
    this->setPixmap(pixmap);
    background->addItem(this);

    update_timer=new QTimer;
    update_timer->start();
    update_timer->setInterval(75);

    show_opacity=new QGraphicsOpacityEffect;
    show_opacityAnimation=new QPropertyAnimation(show_opacity,"opacity");
    hide_opacity=new QGraphicsOpacityEffect;
    hide_opacityAnimation=new QPropertyAnimation(hide_opacity,"opacity");

    this->setGraphicsEffect(show_opacity);
    show_opacityAnimation->setDuration(500);
    show_opacityAnimation->setStartValue(0);
    show_opacityAnimation->setEndValue(1);
    show_opacityAnimation->start();

    connect(update_timer,&QTimer::timeout,this,[=]()
    {
        if(this->collidesWithItem(soul->hitbox)) collide_with_soul=true;
        else collide_with_soul=false;

        if(collide_with_soul&&soul->nowhp>=1) soul->hurt();
    });
}

void Sword::move(int x)

{
    QTimer *wait_timer=new QTimer;
    QTimer *move_timer=new QTimer;
    QTimer *hide_timer=new QTimer;
    wait_timer->setSingleShot(true);
    hide_timer->setSingleShot(true);
    wait_timer->start(500);

    connect(wait_timer,&QTimer::timeout,this,[=]()
    {
        move_timer->start(3);
    });

    connect(move_timer,&QTimer::timeout,this,[=]()
    {
        if(x>0) this->setPos(this->x()+1,this->y());
        if(x<0) this->setPos(this->x()-1,this->y());

        i++;

        if(i==x||i==-x)
        {
            move_timer->stop();
            hide_timer->start(1050);
        }
    });

    connect(hide_timer,&QTimer::timeout,this,[=]()
    {
        update_timer->stop();
        this->setGraphicsEffect(hide_opacity);
        hide_opacityAnimation->setDuration(300);
        hide_opacityAnimation->setStartValue(1);
        hide_opacityAnimation->setEndValue(0);
        hide_opacityAnimation->start();
    });

    connect(hide_opacityAnimation,&QPropertyAnimation::finished,this,[=]()
    {
        update_timer->stop();
        this->hide();
        emit show_finished();
    });
}
