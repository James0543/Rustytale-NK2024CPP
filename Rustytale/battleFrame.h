#ifndef BATTLEFRAME_H
#define BATTLEFRAME_H

#include <QGraphicsRectItem>
#include<QGraphicsPixmapItem>
#include<QTransform>
#include<QPixmap>
#include<QPainter>
#include<QTimer>
#include<QObject>
#include<QString>
#include<QRect>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include"Soul.h"

class battleFrame : public QGraphicsRectItem,public QObject
{
public:
    battleFrame();
    ~battleFrame();
    QGraphicsRectItem *battle_frame_in;
    QGraphicsLineItem *edge_up;
    QGraphicsLineItem *edge_left;
    QGraphicsLineItem *edge_down;
    QGraphicsLineItem *edge_right;

    QGraphicsPixmapItem *target;

    Soul *soul;

    void show_fight_itf();
    void show_act_itf();
    void show_item_itf();
    void show_mercy_itf();

    //定位的玩意。蠢办法。
    int frame_x;
    int frame_y;
    int frame_width;
    int frame_height;

    int frame_in_x;
    int frame_in_y;
    int frame_in_width;
    int frame_in_height;

signals:
    void start_attack();

public slots:
    void expand(int i,int t);
    void shrink(int i,int t);

};

#endif // BATTLEFRAME_H
