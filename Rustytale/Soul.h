#ifndef SOUL_H
#define SOUL_H

#include <QGraphicsPixmapItem>
#include<QMediaPlayer>
#include<QPointF>
#include<QTimer>
#include<QGraphicsRectItem>
#include<QVector2D>

class Soul : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Soul();
    ~Soul();
    QPixmap pixmap;
    QVector2D *vsoul;
    int vup;
    int vleft;
    int vdown;
    int vright;

    int maxhp=20;
    int nowhp=20;

    bool collides_up=false;
    bool collides_left=false;
    bool collides_down=false;
    bool collides_right=false;

    bool moving_up=false;
    bool moving_left=false;
    bool moving_down=false;
    bool moving_right=false;

    bool can_move=true;
    bool drank_bloodmary=false;

    void setv();
    void updatePos();

    void hurt();
    void heal(int h);
    QMediaPlayer *hurt_sound;
    QMediaPlayer *heal_sound;

    bool blue_mode=false;
    QGraphicsRectItem *hitbox;

    bool debug_mode=true;

signals:
    void hp_change();
};

#endif // SOUL_H
