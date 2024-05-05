#include "gunShoot.h"

gunShoot::gunShoot(Soul *soul,QGraphicsScene *background)
{
    QPixmap pixmap=QPixmap(":/image/image/crosshair.png");
    QPixmap pixmap2=QPixmap(":/image/image/shoot.png");
    this->setPixmap(pixmap);
    background->addItem(this);

    show_opacity=new QGraphicsOpacityEffect;
    show_opacityAnimation=new QPropertyAnimation(show_opacity,"opacity");
    hide_opacity=new QGraphicsOpacityEffect;
    hide_opacityAnimation=new QPropertyAnimation(hide_opacity,"opacity");

    this->setGraphicsEffect(show_opacity);
    show_opacityAnimation->setDuration(300);
    show_opacityAnimation->setStartValue(0);
    show_opacityAnimation->setEndValue(1);
    show_opacityAnimation->start();

    load=new QMediaPlayer;
    shoot=new QMediaPlayer;
    load->setMedia(QUrl("qrc:/audio/audio/load.wav"));
    load->setVolume(30);
    shoot->setMedia(QUrl("qrc:/audio/audio/shoot.wav"));
    shoot->setVolume(30);



    if(soul->nowhp>=1)load->play();

    timer=new QTimer;
    timer->setSingleShot(true);
    timer->start(400);

    timer2=new QTimer;
    timer2->setSingleShot(true);
    timer2->start(900);

    hit_circle=new QGraphicsEllipseItem(this->x()+25,this->y()+25,30,30,this);
    hit_circle->hide();

    connect(timer,&QTimer::timeout,this,[=]()
    {
        if(soul->nowhp>=1)shoot->play();
        this->setPixmap(pixmap2);
        if(hit_circle->collidesWithItem(soul->hitbox)) soul->hurt();
    });

    connect(timer2,&QTimer::timeout,this,[=]()
    {
        this->setGraphicsEffect(hide_opacity);
        hide_opacityAnimation->setDuration(200);
        hide_opacityAnimation->setStartValue(1);
        hide_opacityAnimation->setEndValue(0);
        hide_opacityAnimation->start();
    });

    connect(hide_opacityAnimation,&QPropertyAnimation::finished,this,[=]()
    {
        this->hide();
        emit shoot_finished();
    });

}
