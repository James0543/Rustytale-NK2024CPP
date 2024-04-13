#include "gameEngine.h"
#include<QDebug>
#include<math.h>

gameEngine::gameEngine()
{
    //初始化场景
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    background =new QGraphicsScene;
    background->setBackgroundBrush(Qt::black);
    background->setSceneRect(0,0,640,480);


    //初始化界面文本
    QString str1("Lv 7");
    QString str2("hp");
    QString str3("44");
    QString str4("/ ");

    lv=new QGraphicsTextItem(str1);
    hp=new QGraphicsTextItem(str2);
    nowhp=new QGraphicsTextItem(str3);
    maxhp=new QGraphicsTextItem(str4 + str3);

    lv->setFont(QFont("Mars Needs Cunnilingus",12));
    lv->setDefaultTextColor(Qt::white);
    lv->setPos(50,393);
    hp->setFont(QFont("Mars Needs Cunnilingus",10));
    hp->setDefaultTextColor(Qt::white);
    hp->setPos(240,395);
    nowhp->setFont(QFont("Mars Needs Cunnilingus",12));
    nowhp->setDefaultTextColor(Qt::white);
    nowhp->setPos(350,393);
    maxhp->setFont(QFont("Mars Needs Cunnilingus",12));
    maxhp->setDefaultTextColor(Qt::white);
    maxhp->setPos(390,393);
    background->addItem(lv);
    background->addItem(hp);
    background->addItem(nowhp);
    background->addItem(maxhp);

    r_healthbar=new QGraphicsRectItem(277,396,66,20);
    r_healthbar->setBrush(Qt::red);
    background->addItem(r_healthbar);
    y_healthbar=new QGraphicsRectItem(277,396,44,20);
    y_healthbar->setBrush(Qt::yellow);
    background->addItem(y_healthbar);

    //初始化战斗框
    battle_frame= new battleFrame;
    background->addItem(battle_frame);
    battle_frame->battle_frame_in->setFlag(QGraphicsItem::ItemClipsChildrenToShape);


    //初始化按钮
    fight=new QLabel;
    fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight.png);}");
    fight->resize(110,42);
    background->addWidget(fight);
    fight->move(32,425);

    act=new QLabel;
    act->setStyleSheet("QLabel{background-image: url(:/image/image/act.png);}");
    act->resize(110,42);
    background->addWidget(act);
    act->move(187,425);

    item=new QLabel;
    item->setStyleSheet("QLabel{background-image: url(:/image/image/item.png);}");
    item->resize(110,42);
    background->addWidget(item);
    item->move(343,425);

    mercy=new QLabel;
    mercy->setStyleSheet("QLabel{background-image: url(:/image/image/mercy.png);}");
    mercy->resize(110,42);
    background->addWidget(mercy);
    mercy->move(498,425);

    background->addItem(battle_frame->soul);
    battle_frame->soul->setPos(320,300);
    timer=new QTimer;
    timer->setInterval(7);


    //决心移动
    connect(timer,&QTimer::timeout,battle_frame->soul,[=]()
    {
        battle_frame->soul->setv();
        battle_frame->soul->updatePos();
    });
    connect(timer,SIGNAL(timeout()),this,SLOT(collides_check()));
    timer->start();


    //初始化敌人立绘
    enemy_lbl=new QLabel(this);
    enemy_gif=new QMovie(":/anime/anime/jacob.gif");
    enemy_lbl->setMovie(enemy_gif);
    enemy_lbl->setMaximumSize(150,220);
    enemy_lbl->setMinimumSize(150,220);
    enemy_gif->start();
    enemy_lbl->move(255,10);
    background->addWidget(enemy_lbl);


    //初始化音效
    select=new QMediaPlayer;
    select->setMedia(QUrl("qrc:/audio/audio/select.wav"));
    select->setVolume(50);
    confirm=new QMediaPlayer;
    confirm->setMedia(QUrl("qrc:/audio/audio/confirm.wav"));
    confirm->setVolume(50);
    text=new QMediaPlayer;
    text->setMedia(QUrl("qrc:/audio/audio/text.wav"));
    text->setVolume(100);


    //初始化bgm
    battle_bgm_1=new QSoundEffect;
    battle_bgm_1->setSource(QUrl::fromLocalFile(":/audio/audio/battle_bgm_1.wav"));
    battle_bgm_1->setVolume(0.2);
    battle_bgm_1->setLoopCount(999);


    //初始化对话框
    QPixmap bubble1=QPixmap(":/image/image/bubble_1.png");
    QPixmap bubble2=QPixmap(":/image/image/bubble_2.png");
    dialog_bubble_1=new QGraphicsPixmapItem;
    dialog_bubble_2=new QGraphicsPixmapItem;
    dialog_bubble_1->setPixmap(bubble1);
    dialog_bubble_2->setPixmap(bubble2);
    dialog_bubble_1->setZValue(1);
    dialog_bubble_2->setZValue(1);


    //主流程
    this->setScene(background);
    battle_frame->shrink(25,15);

    global_timer=new QTimer;
    global_timer->setSingleShot(true);
    global_timer->setInterval(2000);
    global_timer->start();

    connect(global_timer,&QTimer::timeout,this,[=]()
    {
        show_dialog("测试文本");
        disconnect(global_timer,0,0,0);
        delete global_timer;
        emit start();

    });

    connect(this,&gameEngine::start,battle_frame,[=]()
    {
         global_timer=new QTimer;
         global_timer->setSingleShot(true);
         global_timer->setInterval(1000);
         global_timer->start();
         connect(global_timer,&QTimer::timeout,this,[=]()
         {
             erase_dialog();
             battle_frame->expand(110,5);
             fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
             battle_frame->soul->setPos(32+8,425+13);
             is_players_turn=true;
             disconnect(global_timer,0,0,0);
             delete global_timer;
         });

         global_timer2=new QTimer;
         global_timer2->setSingleShot(true);
         global_timer2->setInterval(1600);
         global_timer2->start();
         connect(global_timer2,&QTimer::timeout,this,[=]()
         {
             battle_bgm_1->play();
             show_text("*测试文本");
             disconnect(global_timer2,0,0,0);
             delete global_timer2;
         });
    });


}



void gameEngine::keyPressEvent(QKeyEvent *k)
{
    if(!is_players_turn)
    {
        switch(k->key())
        {
            case Qt::Key_Up:
            if(!battle_frame->soul->collides_up) battle_frame->soul->vup=1;
            break;

            case Qt::Key_Left:
            if(!battle_frame->soul->collides_left) battle_frame->soul->vleft=1;
            break;

            case Qt::Key_Down:
            if(!battle_frame->soul->collides_down) battle_frame->soul->vdown=1;
            break;

            case Qt::Key_Right:
            if(!battle_frame->soul->collides_right) battle_frame->soul->vright=1;
            break;

            case Qt::Key_P:
            battle_frame->expand(55,7);
            break;

            case Qt::Key_L:
            battle_frame->shrink(55,7);
            break;

            case Qt::Key_M:
            is_players_turn=!is_players_turn;
            break;

            case Qt::Key_B:
            battle_bgm_1->play();
            break;

            case Qt::Key_Y:
            show_dialog("Hello");
            break;

            case Qt::Key_U:
            erase_dialog();
            break;

        }
    }

    //战斗按钮切换，之后再换一下美术资源
    if(is_players_turn)
    {
        if(k->key()==Qt::Key_Right)
        {
            select->play();
            button_index++;
            if(button_index>=5) button_index=1;
            switch(button_index)
            {
                case 1:
                fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
                mercy->setStyleSheet("QLabel{background-image: url(:/image/image/mercy.png);}");
                battle_frame->soul->setPos(32+8,425+13);
                break;

                case 2:
                act->setStyleSheet("QLabel{background-image: url(:/image/image/act_hover.png);}");
                fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight.png);}");
                battle_frame->soul->setPos(187+10,425+13);
                break;

                case 3:
                item->setStyleSheet("QLabel{background-image: url(:/image/image/item_hover.png);}");
                act->setStyleSheet("QLabel{background-image: url(:/image/image/act.png);}");
                battle_frame->soul->setPos(343+7,425+13);
                break;

                case 4:
                mercy->setStyleSheet("QLabel{background-image: url(:/image/image/mercy_hover.png);}");
                item->setStyleSheet("QLabel{background-image: url(:/image/image/item.png);}");
                battle_frame->soul->setPos(498+7,425+13);
                break;
            }
        }
        if(k->key()==Qt::Key_Left)
        {
            select->play();
            button_index--;
            if(button_index<=0) button_index=4;
            switch(button_index)
            {
                case 1:
                fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
                act->setStyleSheet("QLabel{background-image: url(:/image/image/act.png);}");
                battle_frame->soul->setPos(32+8,425+13);
                break;

                case 2:
                act->setStyleSheet("QLabel{background-image: url(:/image/image/act_hover.png);}");
                item->setStyleSheet("QLabel{background-image: url(:/image/image/item.png);}");
                battle_frame->soul->setPos(187+10,425+13);
                break;

                case 3:
                item->setStyleSheet("QLabel{background-image: url(:/image/image/item_hover.png);}");
                mercy->setStyleSheet("QLabel{background-image: url(:/image/image/mercy.png);}");
                battle_frame->soul->setPos(343+7,425+13);
                break;

                case 4:
                mercy->setStyleSheet("QLabel{background-image: url(:/image/image/mercy_hover.png);}");
                fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight.png);}");
                battle_frame->soul->setPos(498+7,425+13);
                break;
            }
        }
        if(k->key()==Qt::Key_Z||k->key()==Qt::Key_Return)
        {
            confirm->play();
            switch(button_index)
            {
                case 1:
                if(!is_fighting)
                {
                    erase_text();
                    battle_frame->show_fight_itf();
                    is_fighting=1;
                }
                else if(is_fighting)
                {
                    battle_frame->shrink(110,5);
                    battle_frame->soul->setPos(320,240);
                    battle();
                }
                break;
            }
        }
    }
}




void gameEngine::keyReleaseEvent(QKeyEvent *k)
{
    switch(k->key())
    {
        case Qt::Key_Up:
        battle_frame->soul->vup=0;
        break;

        case Qt::Key_Left:
        battle_frame->soul->vleft=0;
        break;

        case Qt::Key_Down:
        battle_frame->soul->vdown=0;
        break;

        case Qt::Key_Right:
        battle_frame->soul->vright=0;
        break;
    }
}


void gameEngine::collides_check()
{
    if(battle_frame->edge_up->collidesWithItem(battle_frame->soul)) {battle_frame->soul->collides_up=true;battle_frame->soul->vup=0;}
    else battle_frame->soul->collides_up=false;

    if(battle_frame->edge_left->collidesWithItem(battle_frame->soul)) {battle_frame->soul->collides_left=true;battle_frame->soul->vleft=0;}
    else battle_frame->soul->collides_left=false;

    if(battle_frame->edge_down->collidesWithItem(battle_frame->soul)) {battle_frame->soul->collides_down=true;battle_frame->soul->vdown=0;}
    else battle_frame->soul->collides_down=false;

    if(battle_frame->edge_right->collidesWithItem(battle_frame->soul)) {battle_frame->soul->collides_right=true;battle_frame->soul->vright=0;}
    else battle_frame->soul->collides_right=false;
}


void gameEngine::show_text(QString str)
{
    int n=str.length();
    QTimer *text_timer=new QTimer;
    text_timer->setInterval(50);
    text_timer->start();
    v.resize(n);

    for(int i=0;i<=n-1;i++)
    {
        v[i]=new QGraphicsSimpleTextItem;
        v[i]->setFont(QFont("fzxs12",12));
        v[i]->setText(QString(str[i]));
    }

    connect(text_timer,&QTimer::timeout,this,[=]()
    {
        static int i=0;
        v[i]->setPos(this->battle_frame->frame_x+30+30*i,this->battle_frame->frame_y+20);
        v[i]->setBrush(Qt::white);
        background->addItem(v[i]);
        text->play();
        i++;
        if(i==n)
        {
            text_timer->stop();
            delete text_timer;
            i=0;
            emit show_text_finished();
        }
    });
}


void gameEngine::show_dialog(QString str)
{
    int n=str.length();
    QTimer *dialog_timer=new QTimer;
    dialog_timer->setInterval(50);
    dialog_timer->start();
    dia.resize(n);

    for(int i=0;i<=n-1;i++)
    {
        dia[i]=new QGraphicsSimpleTextItem;
        dia[i]->setText(QString(str[i]));
        dia[i]->setZValue(100);
    }

    if(!is_dialoging) {background->addItem(dialog_bubble_1);is_dialoging=true;}
    dialog_bubble_1->setZValue(-1);
    dialog_bubble_1->setPos(410,50);
    connect(dialog_timer,&QTimer::timeout,this,[=]()
    {
        static int i=0;
        dia[i]->setPos(dialog_bubble_1->x()+18+20*i,dialog_bubble_1->y()+18);
        dia[i]->setBrush(Qt::black);
        background->addItem(dia[i]);
        i++;
        if(i==n)
        {
            dialog_timer->stop();
            delete dialog_timer;
            i=0;
        }
    });
}


void gameEngine::erase_text()
{
    for(int i=0;i<=v.size()-1;i++)
        delete v[i];
}

void gameEngine::erase_dialog()
{
    for(int i=0;i<=dia.size()-1;i++)
        delete dia[i];
    background->removeItem(dialog_bubble_1);

}

gameEngine::~gameEngine()
{
    delete this;
}

void gameEngine::battle()
{
    switch(turn)
    {
        case  1:
        attacks.resize(30);
        for(int i=1;i<=10;i++)
        {
            attacks[i]=new normalAttack(250-20*i,240,10,10+5*i,battle_frame->soul);
            attacks[i]->setParentItem(battle_frame->battle_frame_in);
        }
        for(int i=1;i<=10;i++)
            background->addItem(attacks[i]);
        for(int i=1;i<=10;i++)
            attacks[i]->attackMove(10,200000);

    }
}

