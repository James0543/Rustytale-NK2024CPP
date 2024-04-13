#ifndef SOUL_H
#define SOUL_H

#include <QGraphicsPixmapItem>
#include<QPointF>
#include<QTimer>
#include<QVector2D>

class Soul : public QGraphicsPixmapItem,public QObject
{
public:
    Soul();
    ~Soul();
    QPixmap pixmap;
    QVector2D *vsoul;
    int vup;
    int vleft;
    int vdown;
    int vright;

    int maxhp=44;
    int nowhp=44;

    bool collides_up=false;
    bool collides_left=false;
    bool collides_down=false;
    bool collides_right=false;

    bool moving_up=false;
    bool moving_left=false;
    bool moving_down=false;
    bool moving_right=false;

    void setv();
    void updatePos();

    void hurt();

    bool blue_mode=false;

};

#endif // SOUL_H
