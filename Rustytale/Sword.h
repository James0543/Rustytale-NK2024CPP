#ifndef SWORD_H
#define SWORD_H

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

class Sword : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int i=1;
    bool collide_with_soul=false;
    Sword(Soul *soul,QGraphicsScene *background);
    void move(int x);

    QTimer *update_timer;

    QGraphicsOpacityEffect *show_opacity;
    QPropertyAnimation *show_opacityAnimation;

    QGraphicsOpacityEffect *hide_opacity;
    QPropertyAnimation *hide_opacityAnimation;

signals:
    void show_finished();
};

#endif // SWORD_H
