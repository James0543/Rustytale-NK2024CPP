#include "Soul.h"
#include<QDebug>

Soul::Soul()
{
    pixmap=QPixmap(":/image/image/soul.png");
    this->setPixmap(pixmap);
    vsoul=new QVector2D(0,0);
    vup=vleft=vdown=vright=0;

    hurt_sound=new QMediaPlayer;
    hurt_sound->setMedia(QUrl("qrc:/audio/audio/hurt.wav"));
    hurt_sound->setVolume(100);

    heal_sound=new QMediaPlayer;
    heal_sound->setMedia(QUrl("qrc:/audio/audio/heal.wav"));
    heal_sound->setVolume(100);


    hitbox=new QGraphicsRectItem(this->x()+4,this->y()+4,8,8);
}

Soul::~Soul()
{
    deleteLater();
}

void Soul::setv()
{
    this->vsoul->setX(this->vright-this->vleft);
    this->vsoul->setY(this->vdown-this->vup);
}

void Soul::updatePos()
{
    if(can_move)
    {
        this->setPos(this->x()+vsoul->x(),this->y()+vsoul->y());
        hitbox->setRect(this->x()+4,this->y()+4,8,8);
    }
}

void Soul::hurt()
{
    //qDebug()<<"i am hurt!";
    if(nowhp>=1)
    {
        hurt_sound->stop();
        hurt_sound->play();
    }
    nowhp--;
    emit hp_change();

    if(debug_mode)
    {
        if(nowhp!=20) nowhp=20;
    }
}


void Soul::heal(int h)
{
    heal_sound->stop();
    heal_sound->play();
    if(nowhp+h>=21)
    {
        nowhp=20;
    }
    else
        nowhp=nowhp+h;
    emit hp_change();
}
