#include "targetBar.h"

targetBar::targetBar()
{
    this->setRect(30,245,18,138);
    bar_in=new QGraphicsRectItem;
    bar_in->setRect(34,249,10,130);
    bar_in->setParentItem(this);
    this->setBrush(Qt::black);
    bar_in->setBrush(Qt::white);

    bartimer=new QTimer;
}

void targetBar::bar_move()
{
    this->setPos(30,this->y());
    is_stopped=0;
    this->show();
    bartimer->setInterval(6);
    bartimer->start();
    connect(bartimer,&QTimer::timeout,this,[=]()
    {
        if(!is_stopped)
        {
            this->setPos(this->x()+2,this->y());
        }
        if(this->x()>=560) this->bar_stop();
    });
}

void targetBar::bar_stop()
{
    is_stopped=1;
    bartimer->stop();
    disconnect(bartimer,&QTimer::timeout,0,0);
    bartimer->setInterval(50);
    bartimer->start();
    connect(bartimer,&QTimer::timeout,this,[=]()
    {
        static int i=1;
        if(color)
        {
            this->setBrush(Qt::white);
            bar_in->setBrush(Qt::black);
        }
        else
        {
            this->setBrush(Qt::black);
            bar_in->setBrush(Qt::white);
        }
        color=!color;
        i++;
        if(i==25)
        {
            bartimer->stop();
            disconnect(bartimer,&QTimer::timeout,0,0);
            this->hide();
            emit stopped();
            i=1;
        }
    });
}

targetBar::~targetBar()
{
    deleteLater();
}
