#ifndef GUNSHOOT_H
#define GUNSHOOT_H

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

class gunShoot : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    QTimer *timer;
    QTimer *timer2;
    gunShoot(Soul *soul,QGraphicsScene *background);
    QMediaPlayer *load;
    QMediaPlayer *shoot;
    QGraphicsEllipseItem *hit_circle;

    QGraphicsOpacityEffect *show_opacity;
    QPropertyAnimation *show_opacityAnimation;

    QGraphicsOpacityEffect *hide_opacity;
    QPropertyAnimation *hide_opacityAnimation;

signals:
    void shoot_finished();
};

#endif // GUNSHOOT_H
