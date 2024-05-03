#include "battleFrame.h"
#include<QDebug>

battleFrame::battleFrame()
{
    frame_x=245-50;
    frame_y=240;
    frame_width=150+100;
    frame_height=150;

    frame_in_x=250-50;
    frame_in_y=245;
    frame_in_width=140+100;
    frame_in_height=140;

    this->setRect(frame_x,frame_y,frame_width,frame_height);
    this->setBrush(Qt::white);
    battle_frame_in= new QGraphicsRectItem(this);
    battle_frame_in->setRect(frame_in_x,frame_in_y,frame_in_width,frame_in_height);
    battle_frame_in->setBrush(Qt::black);


    edge_up=new QGraphicsLineItem(frame_in_x,frame_in_y,frame_in_x+frame_in_width,frame_in_y);
    edge_left=new QGraphicsLineItem(frame_in_x,frame_in_y,frame_in_x,frame_in_y+frame_height);
    edge_down=new QGraphicsLineItem(frame_in_x,frame_in_y+frame_height,frame_in_x+frame_in_width,frame_in_y+frame_height);
    edge_right=new QGraphicsLineItem(frame_in_x+frame_in_width,frame_in_y,frame_in_x+frame_in_width,frame_in_y+frame_height);

    soul=new Soul;
    soul->setZValue(10001);

    target= new QGraphicsPixmapItem;
}

void battleFrame::expand(int i,int t)
{
    QTimer *exp1_timer=new QTimer;
    exp1_timer->setInterval(t);
    exp1_timer->start();
    connect(exp1_timer,&QTimer::timeout,this,[=]()
    {
        static int cnt=1;
        frame_x-=2;
        frame_width+=4;
        frame_in_x-=2;
        frame_in_width+=4;

        this->setRect(frame_x,frame_y,frame_width,frame_height);
        battle_frame_in->setRect(frame_in_x,frame_in_y,frame_in_width,frame_in_height);
        edge_up->setLine(frame_in_x,frame_in_y,frame_in_x+frame_in_width,frame_in_y);
        edge_left->setLine(frame_in_x,frame_in_y,frame_in_x,frame_in_y+frame_in_height);
        edge_down->setLine(frame_in_x,frame_in_y+frame_in_height,frame_in_x+frame_in_width,frame_in_y+frame_in_height);
        edge_right->setLine(frame_in_x+frame_in_width,frame_in_y,frame_in_x+frame_in_width,frame_in_y+frame_in_height);

        cnt++;
        if(cnt==i)
        {
            exp1_timer->stop();
            delete exp1_timer;
            cnt=1;
            emit expand_finished();
        }
    });
}

void battleFrame::shrink(int i,int t)
{
    QTimer *srk1_timer=new QTimer;
    srk1_timer->setInterval(t);
    srk1_timer->start();
    connect(srk1_timer,&QTimer::timeout,this,[=]()
    {
        static int cnt=1;
        frame_x+=2;
        frame_width-=4;
        frame_in_x+=2;
        frame_in_width-=4;

        this->setRect(frame_x,frame_y,frame_width,frame_height);
        battle_frame_in->setRect(frame_in_x,frame_in_y,frame_in_width,frame_in_height);
        edge_up->setLine(frame_in_x,frame_in_y,frame_in_x+frame_in_width,frame_in_y);
        edge_left->setLine(frame_in_x,frame_in_y,frame_in_x,frame_in_y+frame_in_height);
        edge_down->setLine(frame_in_x,frame_in_y+frame_in_height,frame_in_x+frame_in_width,frame_in_y+frame_in_height);
        edge_right->setLine(frame_in_x+frame_in_width,frame_in_y,frame_in_x+frame_in_width,frame_in_y+frame_in_height);


        cnt++;

        if(cnt==i)
        {
            srk1_timer->stop();
            delete srk1_timer;
            cnt=1;
            emit shrink_finished();
        }
    });
}

void battleFrame::show_fight_itf()
{

    QPixmap pixmap=QPixmap(":/image/image/target.png");
    target->setPixmap(pixmap);
    target->setParentItem(battle_frame_in);
    target->setPos(30+14,257);
    QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
    target->setGraphicsEffect(opacity);
    QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
    opacityAnimation->setDuration(100);
    opacityAnimation->setStartValue(0);
    opacityAnimation->setEndValue(1);
    opacityAnimation->start();
}

battleFrame::~battleFrame()
{
    this->deleteLater();
    delete this;
}
