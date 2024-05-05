#include "deerBlaster.h"

deerBlaster::deerBlaster(Soul* soulptr,QGraphicsScene *background)
{
    soul=soulptr;

    db_fire=new QGraphicsPixmapItem;
    QPixmap pixmap1=QPixmap(":/image/image/DB.png");
    QPixmap pixmap2=QPixmap(":/image/image/db_fire.png");
    this->setPixmap(pixmap1);
    db_fire->setPixmap(pixmap2);
    this->setScale(1.8);
    this->setZValue(10000);

    show_sound=new QMediaPlayer;
    fire_sound=new QMediaPlayer;
    show_sound->setMedia(QUrl("qrc:/audio/audio/show.wav"));
    fire_sound->setMedia(QUrl("qrc:/audio/audio/fire.wav"));
    show_sound->setVolume(80);
    fire_sound->setVolume(100);

    update_timer=new QTimer;
    update_timer->start();
    update_timer->setInterval(75);
    connect(update_timer,&QTimer::timeout,this,[=]()
    {
        if(this->db_fire->collidesWithItem(soulptr->hitbox)) collide_with_soul=true;
        else collide_with_soul=false;
        if(collide_with_soul)
        {
            soul->hurt();
            if(soul->drank_bloodmary) update_timer->stop();
        }
    });

    show_this_opacity=new QGraphicsOpacityEffect;
    show_this_opacityAnimation=new QPropertyAnimation(show_this_opacity,"opacity");
    show_this_opacityAnimation->setDuration(200);
    show_this_opacityAnimation->setStartValue(0);
    show_this_opacityAnimation->setEndValue(1);

    fire_opacity=new QGraphicsOpacityEffect;
    fire_opacityAnimation=new QPropertyAnimation(fire_opacity,"opacity");
    fire_opacityAnimation->setDuration(100);
    fire_opacityAnimation->setStartValue(50);
    fire_opacityAnimation->setEndValue(1);

    fire_erase_opacity=new QGraphicsOpacityEffect;
    fire_erase_opacityAnimation=new QPropertyAnimation(fire_erase_opacity,"opacity");
    fire_erase_opacityAnimation->setDuration(200);
    fire_erase_opacityAnimation->setStartValue(1);
    fire_erase_opacityAnimation->setEndValue(0);

    erase_this_opacity=new QGraphicsOpacityEffect;
    erase_this_opacityAnimation=new QPropertyAnimation(erase_this_opacity,"opacity");
    erase_this_opacityAnimation->setDuration(200);
    erase_this_opacityAnimation->setStartValue(1);
    erase_this_opacityAnimation->setEndValue(0);

    background->addItem(this);
    this->hide();
    background->addItem(db_fire);
    db_fire->hide();
}



void deerBlaster::show_db(int x,int y,int angle,QGraphicsScene *background)
{
    if(soul->nowhp>=1) show_sound->play();

    this->setGraphicsEffect(show_this_opacity);
    show_this_opacityAnimation->start();

    this->setPos(x,y);
    this->setRotation(angle);
    //background->addItem(this);
    this->show();

    //秒后延迟开火
    QTimer *db_timer_2=new QTimer;
    db_timer_2->setSingleShot(true);
    db_timer_2->setInterval(1100);
    db_timer_2->start();
    connect(db_timer_2,&QTimer::timeout,this,[=]()
    {
        db_fire->setPos(this->x()+28*1.8-9,this->y()+90*1.8);
        db_fire->setPos(rotationPos(db_fire->x(),db_fire->y(),angle));
        db_fire->setRotation(angle);
        db_fire->show();
        fire(background);
        //background->addItem(db_fire);
    });

}



void deerBlaster::fire(QGraphicsScene *background)
{
    if(soul->nowhp>=1) fire_sound->play();

    db_fire->setGraphicsEffect(fire_opacity);
    fire_opacityAnimation->start();

    background->addItem(db_fire);
    fire_timer=new QTimer;
    fire_timer->setSingleShot(true);
    fire_timer->setInterval(200);
    erase_timer=new  QTimer;
    erase_timer->setInterval(5);

    connect(fire_opacityAnimation,&QPropertyAnimation::finished,this,[=]()
    {
        fire_timer->start();
    });

    //弹幕停留0.5s
    connect(fire_timer,&QTimer::timeout,this,[=]()
    {
        //消失
        db_fire->setGraphicsEffect(fire_erase_opacity);
        fire_erase_opacityAnimation->start();
        //压缩
        erase_timer->start();
        delete fire_timer;
    });

    connect(erase_timer,&QTimer::timeout,this,[=]()
    {
        if(cnt<=9)
            db_fire->setTransform(QTransform(0.6,0,0,
                                             0,0.6,0,
                                             0, 0 ,1),true);
        cnt++;
        if(cnt==10)
        {
            update_timer->stop();
            erase_timer->stop();
            this->setGraphicsEffect(erase_this_opacity);
            erase_this_opacityAnimation->start();
            delete erase_timer;
            connect(erase_this_opacityAnimation,&QPropertyAnimation::finished,this,[=]
            {
                background->removeItem(db_fire);
                background->removeItem(this);
                emit fire_finished();
            });
            cnt=1;
        }
    });
}


deerBlaster::~deerBlaster()
{
    deleteLater();
}



QPointF deerBlaster::rotationPos(int x,int y,int angle)
{
    return QPointF(this->x()+(x-this->x())*cos(angle*M_PI/180)-(y-this->y())*sin(angle*M_PI/180),this->y()+(x-this->x())*sin(angle*M_PI/180)+(y-this->y())*cos(angle*M_PI/180));
}
