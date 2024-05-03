#ifndef DEERBLASTER_H
#define DEERBLASTER_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QPixmap>
#include<QTimer>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QMediaPlayer>
#include<cmath>
#include"Soul.h"


class deerBlaster:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    int cnt=1;
    QPointF op=this->boundingRect().center();
    deerBlaster(Soul* soulptr);
    ~deerBlaster();
    void show_db(int x,int y,int angle,QGraphicsScene *background);
    QGraphicsPixmapItem  *db_fire;

    QMediaPlayer *show_sound;
    QMediaPlayer *fire_sound;    
    bool collide_with_soul=false;

    QTimer *update_timer;
    QTimer *fire_timer;
    QTimer *erase_timer;

    Soul *soul;

    QPointF rotationPos(int x,int y,int angle);

    QGraphicsOpacityEffect *show_this_opacity;
    QPropertyAnimation *show_this_opacityAnimation;

    QGraphicsOpacityEffect *fire_opacity;
    QPropertyAnimation *fire_opacityAnimation;

    QGraphicsOpacityEffect *fire_erase_opacity;
    QPropertyAnimation *fire_erase_opacityAnimation;

    QGraphicsOpacityEffect *erase_this_opacity;
    QPropertyAnimation *erase_this_opacityAnimation;


public slots:
        void fire(QGraphicsScene *background);

signals:
        void fire_finished();
};

#endif // DEERBLASTER_H
