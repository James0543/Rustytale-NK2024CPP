#include "textShower.h"

textShower::textShower(QString string,QGraphicsScene *background)
{
    str=string;
    text=new QMediaPlayer;
    text->setMedia(QUrl("qrc:/audio/audio/text.wav"));
    text->setVolume(100);

    int n=str.length();
    v.resize(n);
    background_ptr=background;
    for(int i=0;i<=n-1;i++)
    {
        v[i]=new QGraphicsSimpleTextItem;
        v[i]->setFont(QFont("fzxs12",12));
        v[i]->setText(QString(str[i]));
        v[i]->setBrush(Qt::white);
        v[i]->hide();
    }
}

void textShower::show_text(battleFrame *battle_frame,int k)
{
    //emit cannot_press_key();
    int n=str.length();
    text_timer=new QTimer;
    text_timer->setInterval(50);
    text_timer->start();

    connect(text_timer,&QTimer::timeout,this,[=]()
    {
        if(k==0)
        {
            v[i]->setPos(battle_frame->frame_x+30+30*i,battle_frame->frame_y+20);//旁白
        }
        if(k==1)//对象
        {
            v[i]->setPos(battle_frame->frame_x+60+30*i,battle_frame->frame_y+20);
            battle_frame->soul->setPos(battle_frame->frame_x+30,battle_frame->frame_y+25);
        }
        if(k==2) v[i]->setPos(battle_frame->frame_x+60+18*i,battle_frame->frame_y+20);//英文模式
        if(k==4)//英文对象
        {
            v[i]->setPos(battle_frame->frame_x+60+18*i,battle_frame->frame_y+20);
            battle_frame->soul->setPos(battle_frame->frame_x+30,battle_frame->frame_y+25);
        }
        background_ptr->addItem(v[i]);
        v[i]->show();
        text->stop();//这个是打字音效
        text->play();
        if(i<=n-1) i+=1;
        if(i==n)
        {
            text_timer->stop();
            i=0;
            emit show_text_finished();
            //emit can_press_key();
            is_showing_text=true;
        }
    });
}

void textShower::show_text2(int x,int y,QGraphicsScene *fail_background_ptr)
{
    //emit cannot_press_key();
    int n=str.length();
    text_timer=new QTimer;
    text_timer->setInterval(50);
    text_timer->start();

    connect(text_timer,&QTimer::timeout,this,[=]()
    {

        v[i]->setPos(x+30+30*i,y+20);//旁白
        fail_background_ptr->addItem(v[i]);
        v[i]->show();
        text->stop();//这个是打字音效
        text->play();
        if(i<=n-1) i+=1;
        if(i==n)
        {
            text_timer->stop();
            i=0;
            emit show_text_finished();
            //emit can_press_key();
            is_showing_text=true;
        }
    });
}

void textShower::erase_text()
{
    text_timer->stop();
    i=0;
    for(int i=0;i<=v.size()-1;i++)
    {
        v[i]->hide();
    }
    is_showing_text=false;
}

textShower::~textShower()
{
    deleteLater();
}
