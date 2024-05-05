#ifndef TEXTSHOWER_H
#define TEXTSHOWER_H

#include <QObject>
#include<QMediaPlayer>
#include<QTimer>
#include<QFont>
#include<QPainter>
#include<QGraphicsSimpleTextItem>
#include<QGraphicsScene>
#include"battleFrame.h"

class textShower:public QObject
{
    Q_OBJECT

public:
    int i=0;
    bool is_showing_text=false;
    QMediaPlayer *text;
    QTimer *text_timer;
    QString str;

    textShower(QString string,QGraphicsScene *background);
    ~textShower();
    QVector<QGraphicsSimpleTextItem*> v;

    void show_text(battleFrame *battle_frame,int k);
    void show_text2(int x,int y,QGraphicsScene *fail_background_ptr);
    void erase_text();
    void set_text(QString);

    QGraphicsScene *background_ptr;



signals:
    void show_text_finished();
    //void can_press_key();
    //void cannot_press_key();
};

#endif // TEXTSHOWER_H
