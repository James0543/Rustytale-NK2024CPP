#ifndef TARGETBAR_H
#define TARGETBAR_H

#include <QGraphicsRectItem>
#include <QObject>
#include<QTimer>
#include<QGraphicsRectItem>
#include<QPainter>
#include"battleFrame.h"

class targetBar : public QObject,public QGraphicsRectItem
{
    Q_OBJECT

public:
    QTimer *bartimer;
    QGraphicsRectItem *bar_in;

    bool is_stopped=false;
    bool color=true;

    targetBar();
    ~targetBar();

    void bar_move();
    void bar_stop();


signals:
    void stopped();

};

#endif // TARGETBAR_H
