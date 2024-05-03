#ifndef NORMALATTACK_H
#define NORMALATTACK_H

#include <QObject>
#include<QGraphicsRectItem>
#include<QRect>
#include<QPainter>
#include<QTimer>
#include"Soul.h"

class normalAttack : public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    bool collide_with_soul=false;


    explicit normalAttack(QObject *parent = nullptr);
    normalAttack(int x,int y,int width,int height,Soul* soul);
    ~normalAttack();
    void attackMove(int tx,int ty,QTimer *move_timer_x,QTimer *move_timer_y);

    Soul *soulptr;
    QTimer *update_timer;
    /*QTimer *move_timer_x;
    QTimer *move_timer_y;*/


signals:

};

#endif // NORMALATTACK_H
