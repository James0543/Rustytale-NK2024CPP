 #include "gameEngine.h"
#include<QDebug>
#include<math.h>

gameEngine::gameEngine()
{
    this->setRenderHint(QPainter::Antialiasing);//抗锯齿
    this->setRenderHint(QPainter::SmoothPixmapTransform);//设置平滑效果
    setFrameShape(QFrame::NoFrame);//去掉边框

    //初始化场景
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    background =new QGraphicsScene;
    background->setBackgroundBrush(Qt::black);
    background->setSceneRect(0,0,640,480);

    end_scene=new QGraphicsScene;
    end_scene->setBackgroundBrush(Qt::black);
    end_scene->setSceneRect(0,0,640,480);


    //初始化文本
    main_interface1=new textShower("*你下定了决心...",background);
    jacob=new textShower("Jakob",background);
    act_select=new textShower("*查看",background);
    introduce=new textShower("*雅各布，攻击-? 防御-？",background);
    introduce2=new textShower("*天堂岛的落胤，锈湖的统领者",background);
    end_text=new textShower("感谢游玩！",end_scene);


    //初始化界面文本
    debug_mode=new QGraphicsTextItem("Debug Mode");
    debug_mode->setFont(QFont("fzjcxs",12));
    debug_mode->setDefaultTextColor(Qt::white);
    background->addItem(debug_mode);
    debug_mode->hide();

    QString str1("Lv 1");
    QString str2("HP");
    QString str3("20");
    QString str4("/ ");

    lv=new QGraphicsTextItem(str1);
    hp=new QGraphicsPixmapItem;
    nowhp=new QGraphicsTextItem(str3);
    maxhp=new QGraphicsTextItem(str4 + str3);

    lv->setFont(QFont("Mars Needs Cunnilingus",12));
    lv->setDefaultTextColor(Qt::white);
    lv->setPos(50,393);
    hp->setPixmap(QPixmap(":/image/image/hp.png"));
    hp->setPos(220,400);
    nowhp->setFont(QFont("Mars Needs Cunnilingus",12));
    nowhp->setDefaultTextColor(Qt::white);
    nowhp->setPos(395,393);
    maxhp->setFont(QFont("Mars Needs Cunnilingus",12));
    maxhp->setDefaultTextColor(Qt::white);
    maxhp->setPos(440,393);
    background->addItem(lv);
    background->addItem(hp);
    background->addItem(nowhp);
    background->addItem(maxhp);


    //初始化血条
    r_healthbar=new QGraphicsRectItem(254,396,132,20);
    r_healthbar->setBrush(Qt::red);
    r_healthbar->setPen(Qt::NoPen);
    background->addItem(r_healthbar);
    y_healthbar=new QGraphicsRectItem(254,396,132,20);
    y_healthbar->setBrush(Qt::yellow);
    y_healthbar->setPen(Qt::NoPen);
    background->addItem(y_healthbar);


    //初始化战斗框
    battle_frame= new battleFrame;
    background->addItem(battle_frame);
    battle_frame->battle_frame_in->setFlag(QGraphicsItem::ItemClipsChildrenToShape);
    bar=new targetBar();
    background->addItem(bar);
    bar->hide();


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


    //初始化敌人立绘
    enemy_lbl=new QLabel;
    enemy_gif=new QMovie(":/anime/anime/jacob2.gif");
    enemy_wid=new QGraphicsProxyWidget;
    enemy_lbl->setMovie(enemy_gif);
    enemy_lbl->setMaximumSize(100*2,130*2);
    enemy_lbl->setMinimumSize(100*2,130*2);
    enemy_gif->start();
    enemy_wid->setWidget(enemy_lbl);
    background->addItem(enemy_wid);
    enemy_wid->setZValue(-1);
    enemy_wid->setPos(240,5);
    enemy_lbl->setScaledContents(true);


    //初始化音效
    select=new QMediaPlayer;
    select->setMedia(QUrl("qrc:/audio/audio/select.wav"));
    select->setVolume(50);
    confirm=new QMediaPlayer;
    confirm->setMedia(QUrl("qrc:/audio/audio/confirm.wav"));
    confirm->setVolume(50);
    dia_sound=new QMediaPlayer;
    dia_sound->setMedia(QUrl("qrc:/audio/audio/dia_sound.wav"));
    dia_sound->setVolume(100);
    slice_snd=new QMediaPlayer;
    slice_snd->setMedia(QUrl("qrc:/audio/audio/slice.wav"));
    slice_snd->setVolume(50);
    break_snd=new QMediaPlayer;
    break_snd->setMedia(QUrl("qrc:/audio/audio/break.wav"));
    break_snd->setVolume(50);
    pieces_snd=new QMediaPlayer;
    pieces_snd->setMedia(QUrl("qrc:/audio/audio/pieces.wav"));
    pieces_snd->setVolume(50);


    //初始化bgm
    battle_bgm_1=new QSoundEffect;
    battle_bgm_1->setSource(QUrl::fromLocalFile(":/audio/audio/battle_bgm_1.wav"));
    battle_bgm_1->setVolume(0.2);
    battle_bgm_1->setLoopCount(999);
    fail_bgm=new QSoundEffect;
    fail_bgm->setSource(QUrl::fromLocalFile(":/audio/audio/gameover.wav"));
    fail_bgm->setVolume(0.2);
    fail_bgm->setLoopCount(1);


    //初始化对话框
    QPixmap bubble=QPixmap(":/image/image/bubble.png");
    dialog_bubble=new QGraphicsPixmapItem;
    dialog_bubble->setPixmap(bubble);
    dialog_bubble->setZValue(1);


    //初始化攻击贴图
    slice=new QGraphicsPixmapItem;
    QPixmap slice_pixmap=QPixmap(":/image/image/slice0.png");
    slice->setPixmap(slice_pixmap);
    background->addItem(slice);
    slice->hide();
    //slice->setScale(3.0);
    miss=new QGraphicsPixmapItem;
    QPixmap miss_pixmap=QPixmap(":/image/image/miss.png");
    miss->setPixmap(miss_pixmap);
    background->addItem(miss);
    miss->hide();


    //初始化失败结算界面
    heart_break_scene=new QGraphicsScene;
    heart_break_scene->setBackgroundBrush(Qt::black);
    break_soul=new Soul;

    fail_scene=new QGraphicsScene;
    fail_scene->setBackgroundBrush(Qt::black);
    fail_background=new QGraphicsPixmapItem;
    fail_background->setPixmap(QPixmap(":/image/image/fail.png"));


    //初始化道具
    items[1]=Item(20,"* 派","*你吃掉了派","*这是一块美味的派","*你的HP已满",background);
    items[2]=Item(20,"* 蓝色方块","*你使用了蓝色方块","*时间被回溯了","*你的HP已满",background);
    items[3]=Item(6,"* 牛奶","*你喝掉了牛奶","*温暖又甘甜","*你回复了6HP",background);
    items[4]=Item(20,"* 少女之香","*你使用了少女之香","*繧｢繝ｪ繧ｹ縺ｯ縺ｩ縺・","*你的HP已满",background);
    items[5]=Item(1,"* 咖啡","*你喝掉了咖啡","*闻上去就很好喝","*你回复了1HP",background);
    items[6]=Item(0,"* 血腥玛丽","*你喝掉了血腥玛丽","*据说它曾经毒死了一头鹿","*你失去了10HP上限，但是...",background);
    items[7]=Item(1,"* 三明治","*你吃掉了三明治","*它的味道有些不太对劲","*你回复了1HP",background);
    items[8]=Item(6,"* 薯片","*你吃掉了薯片","*嘎嘣嘎嘣脆","*你回复了6HP",background);
    items[9]=Item(10,"* 美洲大树莓","*你吃掉了美洲大树莓","*充满了春天的味道","*你回复了10HP",background);
    items[10]=Item(4,"* 苦艾酒","*你喝掉了苦艾酒","*你的口腔里全是苦味","*你回复了4HP",background);
    for(int i=1;i<=10;i++)
    {
        background->addItem(items[i].name);
        items[i].name->setZValue(11000);
        items[i].name->hide();
    }

    //决心移动
    connect(timer,&QTimer::timeout,battle_frame->soul,[=]()
    {
        battle_frame->soul->setv();
        battle_frame->soul->updatePos();
    });
    connect(timer,SIGNAL(timeout()),this,SLOT(collides_check()));
    timer->start();


    //血量检测与血条刷新
    connect(battle_frame->soul,&Soul::hp_change,this,[=]()
    {
        y_healthbar->setRect(254,396,132*battle_frame->soul->nowhp/battle_frame->soul->maxhp,20);
        QString str=QString::number(battle_frame->soul->nowhp);
        nowhp->setPlainText(str);
        //if(battle_frame->soul->nowhp==0) fail();
        if(battle_frame->soul->nowhp==0)
        {
            this->setScene(heart_break_scene);
            heart_break_scene->addItem(break_soul);
            heart_break_scene->setSceneRect(0,0,640,480);
            break_soul->setPos(battle_frame->soul->x(),battle_frame->soul->y());
            battle_bgm_1->stop();
            fail();
            failed=true;
        }
    });





    //主流程
    this->setScene(background);
    battle_frame->shrink(25,15);

    global_timer=new QTimer;
    global_timer->setSingleShot(true);
    global_timer->setInterval(2000);
    global_timer->start();

    connect(global_timer,&QTimer::timeout,this,[=]()
    {
        show_dialog("我们开始吧。");
        disconnect(global_timer,0,0,0);
        delete global_timer;
        emit start();

    });

    connect(this,&gameEngine::start,battle_frame,[=]()
    {
         global_timer=new QTimer;
         global_timer->setSingleShot(true);
         global_timer->setInterval(800);
         global_timer->start();
         connect(global_timer,&QTimer::timeout,this,[=]()
         {
             is_dialoging=0;
             erase_dialog();
             battle_frame->expand(110,5);
             fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
             battle_frame->soul->setPos(32+8,425+13);
             battle_frame->soul->can_move=false;
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
             main_interface1->show_text(battle_frame,0);
             connect(main_interface1,&textShower::show_text_finished,this,[=]()
             {
                 disconnect(main_interface1,&textShower::show_text_finished,0,0);
                 is_players_turn=true;
             });
             disconnect(global_timer2,0,0,0);
             delete global_timer2;
         });

    });

    //is_players_turn=1;
    //battle_frame->expand(110,5);

}



void gameEngine::keyPressEvent(QKeyEvent *k)
{
    if(k->key()==Qt::Key_F4)
    {
        change_size();
    }

    if(!failed)
    {
        if(!is_players_turn)
        {
            if(k->key()==up)
                if(!battle_frame->soul->collides_up) battle_frame->soul->vup=1;

            if(k->key()==left)
                if(!battle_frame->soul->collides_left) battle_frame->soul->vleft=1;

            if(k->key()==down)
                if(!battle_frame->soul->collides_down) battle_frame->soul->vdown=1;

            if(k->key()==right)
                if(!battle_frame->soul->collides_right) battle_frame->soul->vright=1;

            if(k->key()==Qt::Key_K)
            {
                static bool debug=true;
                if(debug)
                {
                    battle_frame->soul->debug_mode=true;
                    debug_mode->show();
                    debug=false;
                }
               else
               {
                    battle_frame->soul->debug_mode=false;
                    debug_mode->hide();
                    debug=true;
                }
            }
        }

        //战斗按钮切换
        if(is_players_turn)
        {
            if(k->key()==right  &&!is_showing_target&&!is_fighting&&!bar_moving&&!is_selecting&&!acted&&!is_showing_item&&!is_using_item&&!used_item)
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
            if(k->key()==left  &&!is_showing_target&&!is_fighting&&!bar_moving&&!is_selecting&&!acted&&!is_showing_item&&!is_using_item&&!used_item)
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
            if(k->key()==up)
            {
                if(is_showing_item)
                {
                    hide_item_list(show_item_index);
                    if(focus_item_index==1&&show_item_index>=2) show_item_index--;
                    if(focus_item_index>=2) focus_item_index--;
                    show_item_list(show_item_index);
                    set_soul_to_item(focus_item_index);
                }
            }
            if(k->key()==down)
            {
                if(is_showing_item)
                {
                    hide_item_list(show_item_index);
                    if(focus_item_index==3&&show_item_index<=item_number-3) show_item_index++;
                    if(focus_item_index<=2) focus_item_index++;
                    show_item_list(show_item_index);
                    set_soul_to_item(focus_item_index);
                }
            }
            if(k->key()==Qt::Key_Z||k->key()==Qt::Key_Return)
            {
                confirm->play();
                switch(button_index)
                {
                    case 1:
                    main_interface1->erase_text();
                    if((is_showing_target==false)&&(bar_moving==false))
                    {
                        jacob->show_text(battle_frame,4);
                        is_showing_target=true;
                    }
                    else if((is_showing_target==true)&&(bar_moving==false))
                    {
                        fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight.png);}");
                        jacob->erase_text();
                        battle_frame->show_fight_itf();
                        battle_frame->target->show();
                        bar->show();
                        bar->bar_move();
                        battle_frame->soul->hide();
                        bar_moving=true;
                        disconnect(bar,&targetBar::stopped,0,0);
                        connect(bar,&targetBar::stopped,this,[=]()
                        {
                            if(turn!=3) battle_frame->shrink(110,5);
                            else battle_frame->shrink(140,5);
                            battle_frame->target->hide();
                            disconnect(battle_frame,SIGNAL(shrink_finished()),0,0);
                            connect(battle_frame,&battleFrame::shrink_finished,this,[=]()
                            {
                                battle();
                            });
                            is_players_turn=false;
                        });
                    }
                    else if((is_showing_target==true)&&(bar_moving==true))
                    {
                        bar->bar_stop();
                        if(!attacked) player_attack();
                    }
                    break;


                    case 2:
                    main_interface1->erase_text();
                    if(is_showing_target==false&&is_selecting==false&&acted==false)
                    {
                        is_showing_target=true;
                        jacob->show_text(battle_frame,4);
                    }
                    else if(is_showing_target==true&&is_selecting==false&&acted==false)
                    {
                        jacob->erase_text();
                        act_select->show_text(battle_frame,1);
                        is_selecting=true;
                    }
                    else if(is_showing_target==true&&is_selecting==true&&acted==false)
                    {
                        act_select->erase_text();
                        introduce->show_text(battle_frame,0);
                        battle_frame->soul->hide();
                        act->setStyleSheet("QLabel{background-image: url(:/image/image/act.png);}");

                        connect(introduce,&textShower::show_text_finished,this,[=]()
                        {
                            disconnect(introduce,&textShower::show_text_finished,0,0);
                            introduce2->show_text2(20,280,background);
                        });

                        connect(introduce2,&textShower::show_text_finished,this,[=]()
                        {
                            disconnect(introduce2,&textShower::show_text_finished,0,0);
                            acted=true;
                        });
                    }
                    else if(is_showing_target==true&&is_selecting==true&&acted==true)
                    {
                        is_showing_target=false;
                        is_selecting=false;
                        acted=false;
                        introduce->erase_text();
                        introduce2->erase_text();
                        main_interface1->show_text(battle_frame,0);
                        battle_frame->soul->setPos(187+10,425+13);
                        act->setStyleSheet("QLabel{background-image: url(:/image/image/act_hover.png);}");
                        battle_frame->soul->show();
                    }
                    break;


                    case 3:
                    main_interface1->erase_text();
                    if(item_number!=0)
                    {
                        if(is_showing_item==false&&is_using_item==false&&used_item==false)
                        {
                            is_showing_item=true;
                            show_item_list(show_item_index);
                            set_soul_to_item(focus_item_index);
                        }
                        else if(is_showing_item==true&&is_using_item==false&&used_item==false)
                        {
                            is_showing_item=false;
                            is_using_item=true;
                            use_item(show_item_index,focus_item_index);
                            connect(items[item_number].heal_msg,&textShower::show_text_finished,this,[=]()
                            {
                                disconnect(items[item_number].heal_msg,&textShower::show_text_finished,0,0);
                                used_item=true;
                            });
                        }
                        else if(is_showing_item==false&&is_using_item==true&&used_item==true)
                        {
                            is_using_item=false;
                            used_item=false;
                            hide_item_message(item_number);
                            item_number--;
                            focus_item_index=1;
                            show_item_index=1;
                            main_interface1->show_text(battle_frame,0);
                            battle_frame->soul->show();
                            item->setStyleSheet("QLabel{background-image: url(:/image/image/item_hover.png);}");
                            battle_frame->soul->setPos(343+7,425+13);
                        }
                    }
                    break;
                }
            }
            if(k->key()==Qt::Key_X)
            {
                switch(button_index)
                {
                    case 1:
                    if((is_showing_target==true)&&(bar_moving==false))
                    {
                        jacob->erase_text();
                        main_interface1->show_text(battle_frame,0);
                        is_showing_target=false;
                        battle_frame->soul->setPos(32+8,425+13);
                    }
                    break;

                    case 2:
                    if((is_showing_target==true)&&(is_selecting==false))
                    {
                        jacob->erase_text();
                        main_interface1->show_text(battle_frame,0);
                        is_showing_target=false;
                        battle_frame->soul->setPos(187+10,425+13);
                    }
                    if(is_showing_target==true&&is_selecting==true)
                    {
                        act_select->erase_text();
                        jacob->show_text(battle_frame,4);
                        is_selecting=false;
                    }
                    break;

                    case 3:
                    if(is_showing_item)
                    {
                        hide_item_list(show_item_index);
                        main_interface1->show_text(battle_frame,0);
                        battle_frame->soul->setPos(343+7,425+13);
                        is_showing_item=false;
                    }
                    if(item_number==0)
                    {
                        main_interface1->show_text(battle_frame,0);
                    }
                    break;
                }
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
        dia[i]->setFont(QFont("fzjcxs",8));
        dia[i]->setZValue(100);
    }

    if(!is_dialoging) {background->addItem(dialog_bubble);is_dialoging=true;}
    dialog_bubble->setZValue(-1);
    dialog_bubble->setPos(420,50);
    connect(dialog_timer,&QTimer::timeout,this,[=]()
    {
        static int i=0;
        //dia_sound->stop();
        //dia_sound->play();
        if(i<=7) dia[i]->setPos(dialog_bubble->x()+26+17*i,dialog_bubble->y()+11);
        else dia[i]->setPos(dialog_bubble->x()+26+17*(i-7),dialog_bubble->y()+22);
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


void gameEngine::erase_dialog()
{
    for(int i=0;i<=dia.size()-1;i++)
        delete dia[i];
    if(!is_dialoging) background->removeItem(dialog_bubble);
}


void gameEngine::player_attack()
{
    attacked=true;
    slice_snd->play();
    background->addItem(slice);
    slice->show();
    slice->setPos(290,100);
    QTimer *slice_timer=new  QTimer;
    slice_timer->start(50);
    static int i=0;
    static int k=1;
    static bool move_left=true;

    connect(slice_timer,&QTimer::timeout,this,[=]()
    {
        if(i==0)
            slice->setPixmap(QPixmap(":/image/image/slice0.png"));
        else if(i==1)
            slice->setPixmap(QPixmap(":/image/image/slice1.png"));
        else if(i==2)
            slice->setPixmap(QPixmap(":/image/image/slice2.png"));
        else if(i==3)
            slice->setPixmap(QPixmap(":/image/image/slice3.png"));
        else if(i==4)
            slice->setPixmap(QPixmap(":/image/image/slice4.png"));
        else if(i==5)
            slice->setPixmap(QPixmap(":/image/image/slice5.png"));
        else
        {
            show_miss();
            slice_timer->stop();
            slice->hide();
            slice->setPixmap(QPixmap(":/image/image/slice0.png"));
            i=0;
            disconnect(slice_timer,&QTimer::timeout,0,0);
        }
        i++;
    });

    QTimer *dre_timer=new QTimer;
    dre_timer->setSingleShot(true);
    dre_timer->start(900);
    connect(dre_timer,&QTimer::timeout,this,[=]()
    {
        move_left=false;
        delete dre_timer;
    });



    QTimer *enemy_timer=new  QTimer;
    enemy_timer->start(10);

    connect(enemy_timer,&QTimer::timeout,this,[=]()
    {
        if(k<=40&&move_left)
        {
            enemy_wid->setPos(enemy_wid->x()-4,enemy_wid->y());
            k++;
        }
        else if(k>=41&&!move_left)
        {
            enemy_wid->setPos(enemy_wid->x()+4,enemy_wid->y());
            k++;
        }
        if(k>=81)
        {
            enemy_timer->stop();
            disconnect(enemy_timer,&QTimer::timeout,0,0);
            k=0;
            move_left=true;
        }
    });
}


gameEngine::~gameEngine()
{
    deleteLater();
}


void gameEngine::change_size()
{
    if(change_sig)
    {
        this->parentWidget()->showFullScreen();
        this->scale(3,3);
        this->setMaximumSize(640*3,480*3);
        this->setMinimumSize(640*3,480*3);
        background->setSceneRect(0,0,640*3,480*3);
        this->move(320,0);
        //控制全屏
        change_sig=!change_sig;
    }
    else
    {
        this->parentWidget()->showNormal();
        this->scale(0.3333333,0.3333333);
        this->setMaximumSize(640,480);
        this->setMinimumSize(640,480);
        background->setSceneRect(0,0,640,480);
        this->move(0,0);
        //控制全屏
        change_sig=!change_sig;
    }
}


void gameEngine::show_miss()
{
    qDebug()<<"Miss!!";
    miss->setPos(251,60);
    miss->show();

    QTimer *miss_timer=new QTimer;
    miss_timer->start(25);
    static int i=1;

    connect(miss_timer,&QTimer::timeout,this,[=]()
    {
        if(i<=10)
            miss->setPos(251,miss->y()-1);
        if(i>=11&&i<=20)
            miss->setPos(251,miss->y()+1);
        if(i==21)
        {
            miss_timer->stop();
            miss->hide();
            i=0;
        }
        i++;
    });
}


void gameEngine::fail()
{
    QTimer *pieces_timer=new QTimer;
    pieces_timer->setSingleShot(true);
    pieces_timer->start(1000);
    QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
    QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
    connect(pieces_timer,&QTimer::timeout,this,[=]()
    {
        break_snd->play();
        break_soul->setPos(break_soul->x()-2,break_soul->y());
        break_soul->setPixmap(QPixmap(":/image/image/heartbreak.png"));
        disconnect(pieces_timer,&QTimer::timeout,0,0);

        QTimer *erase_timer=new QTimer;
        erase_timer->setSingleShot(true);
        erase_timer->start(1000);

        connect(erase_timer,&QTimer::timeout,this,[=]()
        {
            fail_bgm->play();
            break_soul->setGraphicsEffect(opacity);
            opacityAnimation->setDuration(1000);
            opacityAnimation->setStartValue(1);
            opacityAnimation->setEndValue(0);
            opacityAnimation->start();
        });
    });
    connect(opacityAnimation,&QPropertyAnimation::finished,this,[=]()
    {
        this->setScene(fail_scene);
        QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
        QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
        fail_background->setGraphicsEffect(opacity);
        opacityAnimation->setDuration(2000);
        opacityAnimation->setStartValue(0);
        opacityAnimation->setEndValue(1);
        opacityAnimation->start();

        fail_scene->addItem(fail_background);
        textShower *stay_determined=new textShower("保持你的决心...",fail_scene);

        connect(opacityAnimation,&QPropertyAnimation::finished,this,[=]()
        {
            stay_determined->show_text2(160,250,fail_scene);
            disconnect(opacityAnimation,&QPropertyAnimation::finished,0,0);
        });

        QTimer *quit_timer=new QTimer;
        quit_timer->start(3500);
        quit_timer->setSingleShot(true);
        connect(quit_timer,&QTimer::timeout,this,[=]()
        {
            disconnect(quit_timer,&QTimer::timeout,0,0);
            for(int i=0;i<=stay_determined->v.size()-1;i++)
                stay_determined->v[i]->setParentItem(fail_background);
            disconnect(stay_determined,&textShower::show_text_finished,0,0);
            QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
            QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
            fail_background->setGraphicsEffect(opacity);
            opacityAnimation->setDuration(2000);
            opacityAnimation->setStartValue(1);
            opacityAnimation->setEndValue(0);
            opacityAnimation->start();

            QTimer *fade_timer=new QTimer;
            fade_timer->start(200);
            connect(fade_timer,&QTimer::timeout,this,[=]()
            {
                static int i=1;
                fail_bgm->setVolume(0.2-0.02*i);
                i++;
                if(i==11)
                {
                    fade_timer->stop();
                    disconnect(fade_timer,&QTimer::timeout,0,0);
                    i=1;
                    delete fade_timer;
                }
            });

            connect(opacityAnimation,&QPropertyAnimation::finished,this,[=]()
            {
                disconnect(opacityAnimation,&QPropertyAnimation::finished,0,0);
                this->close();
                connect(this,SIGNAL(restart()),this->parentWidget(),SLOT(open_menu()));
                emit restart();
            });
        });

    });
}


void gameEngine::show_item_list(int k)
{
    if(item_number>=3)
    {
        if(k>=1&&k<=item_number-2)
        {
            items[k].name->setPos(80+12,255);
            items[k].name->show();
            items[k+1].name->setPos(80+12,295);
            items[k+1].name->show();
            items[k+2].name->setPos(80+12,335);
            items[k+2].name->show();
        }
    }
    if(item_number==2)
    {
        items[k].name->setPos(80+12,255);
        items[k].name->show();
        items[k+1].name->setPos(80+12,295);
        items[k+1].name->show();
    }
    if(item_number==1)
    {
        items[k].name->setPos(80+12,255);
        items[k].name->show();
    }
    //剩下一个或两个的时候
}


void gameEngine::hide_item_list(int k)
{
    if(item_number>=3)
    {
        items[k].name->hide();
        items[k+1].name->hide();
        items[k+2].name->hide();
    }
    if(item_number==2)
    {
        items[k].name->hide();
        items[k+1].name->hide();
    }
    if(item_number==1)
    {
        items[k].name->hide();
    }
}

void gameEngine::hide_item_message(int k)
{
    items[k].use_msg->erase_text();
    items[k].describe->erase_text();
    items[k].heal_msg->erase_text();
}


void gameEngine::set_soul_to_item(int index)
{
    if(index==1)
        battle_frame->soul->setPos(55,255+10);
    if(index==2)
        battle_frame->soul->setPos(55,295+10);
    if(index==3)
        battle_frame->soul->setPos(55,335+10);

}


void gameEngine::use_item(int show,int focus)
{
    QTimer *use_timer1=new QTimer;
    QTimer *use_timer2=new QTimer;
    use_timer1->setSingleShot(true);
    use_timer2->setSingleShot(true);

    battle_frame->soul->hide();
    item->setStyleSheet("QLabel{background-image: url(:/image/image/item.png);}");
    int index=show+focus-1;
    hide_item_list(show);
    for(int i=index;i<=item_number-1;i++)
        std::swap(items[i],items[i+1]);
    index=item_number;
    if(items[index].item_name!="* 蓝色方块") battle_frame->soul->heal(items[index].heal);
    if(items[index].item_name=="* 蓝色方块")
    {
        //加一个音效
        battle_bgm_1->stop();
        battle_bgm_1->play();
        battle_frame->soul->nowhp=20;
        if(battle_frame->soul->drank_bloodmary)
        {
            battle_frame->soul->maxhp=20;
            battle_frame->soul->drank_bloodmary=false;
        }
        y_healthbar->setRect(254,396,132*battle_frame->soul->nowhp/battle_frame->soul->maxhp,20);
        QString str=QString::number(battle_frame->soul->nowhp);
        nowhp->setPlainText(str);
        QString str2=QString::number(battle_frame->soul->maxhp);
        maxhp->setPlainText("/ "+str2);
        turn=1;
    }
    if(items[index].item_name=="* 血腥玛丽")
    {
        battle_frame->soul->drank_bloodmary=true;
        battle_frame->soul->maxhp=10;
        if(battle_frame->soul->nowhp>=11) battle_frame->soul->nowhp=10;
        QString str=QString::number(battle_frame->soul->nowhp);
        nowhp->setPlainText(str);
        QString str2=QString::number(battle_frame->soul->maxhp);
        maxhp->setPlainText("/ "+str2);
        y_healthbar->setRect(254,396,132*battle_frame->soul->nowhp/battle_frame->soul->maxhp,20);
    }
    items[index].use_msg->show_text(battle_frame,0);
    connect(items[index].use_msg,&textShower::show_text_finished,this,[=]()
    {
        use_timer1->start(300);
        connect(use_timer1,&QTimer::timeout,this,[=]()
        {
            disconnect(use_timer1,&QTimer::timeout,0,0);
            delete use_timer1;
            items[index].describe->show_text2(25,280,background);
        });
    });

    connect(items[index].describe,&textShower::show_text_finished,this,[=]()
    {
        use_timer2->start(300);
        connect(use_timer2,&QTimer::timeout,this,[=]()
        {
            disconnect(use_timer2,&QTimer::timeout,0,0);
            delete use_timer2;
            items[index].heal_msg->show_text2(25,320,background);
        });
    });
    //改成时间计时器
}


void gameEngine::battle()
{
    is_showing_target=false;
    bar_moving=false;
    attacked=false;
    battle_frame->soul->can_move=true;

    /*****************************************************************第一回合*************************************************************************/
    if(turn==1)
    {
        battle_frame->soul->setPos(320,320);
        battle_frame->soul->show();

        QTimer *move_timer_x=new QTimer;
        QTimer *move_timer_y=new QTimer;
        fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight.png);}");
        attacks.resize(50);

        for(int i=1;i<=5;i++)
            attacks[i]=new normalAttack(250-20*i,240,10,6+6*i,battle_frame->soul);

        for(int i=6;i<=10;i++)
            attacks[i]=new normalAttack(250-20*(i-5),240+6+6*(i-5)+35,10,2*(35-6*(i-5)),battle_frame->soul);

        for(int i=11;i<=15;i++)
            attacks[i]=new normalAttack(250-20*(i-10),240+6+6*(i-10)+35  +  2*(35-6*(i-10)) + 35,10,10+4*(i-10),battle_frame->soul);

        for(int i=16;i<=19;i++)
            attacks[i]=new normalAttack(150-20*(i-15),240,10,36-6*(i-15),battle_frame->soul);

        for(int i=20;i<=23;i++)
            attacks[i]=new normalAttack(150-20*(i-19),240+36-6*(i-19)+35,10,2*(5+6*(i-19)),battle_frame->soul);

        for(int i=24;i<=27;i++)
            attacks[i]=new normalAttack(150-20*(i-23),240+36-6*(i-23)+35 + 2*(5+6*(i-23)) + 35,10,30-4*(i-23),battle_frame->soul);

        for(int i=28;i<=31;i++)
            attacks[i]=new normalAttack(70-20*(i-27),240,10,12+6*(i-27),battle_frame->soul);

        for(int i=32;i<=35;i++)
            attacks[i]=new normalAttack(70-20*(i-31),240+12+6*(i-31)+35,10,2*(29-6*(i-31)),battle_frame->soul);

        for(int i=36;i<=39;i++)
            attacks[i]=new normalAttack(70-20*(i-35),240+12+6*(i-35)+35 + 2*(29-6*(i-35)) + 35,10,14+4*(i-35),battle_frame->soul);

        QTimer *turn1_timer=new QTimer;
        turn1_timer->setInterval(1000);
        turn1_timer->setSingleShot(true);
        turn1_timer->start();


        dbs.resize(12);
        for(int i=0;i<=9;i++)
        {
            dbs[i]=new deerBlaster(battle_frame->soul,background);
        }

        connect(turn1_timer,&QTimer::timeout,this,[=]()
        {
            dbs[0]->show_db(80,400,-90,background);
        });



        connect(dbs[0],&deerBlaster::fire_finished,this,[=]()
        {
            dbs[1]->show_db(265,65,0,background);
            dbs[2]->show_db(577,258,90,background);
            dbs[3]->show_db(377,553,180,background);
            dbs[4]->show_db(65,374,-90,background);
            disconnect(dbs[0],&deerBlaster::fire_finished,0,0);
        });

        connect(dbs[4],&deerBlaster::fire_finished,this,[=]()
        {
            dbs[5]->show_db(488,70,45,background);
            dbs[6]->show_db(568,485,135,background);
            dbs[7]->show_db(150,567,225,background);
            dbs[8]->show_db(75,150,315,background);
            disconnect(dbs[4],&deerBlaster::fire_finished,0,0);
        });

        connect(dbs[8],&deerBlaster::fire_finished,this,[=]()
        {
            dbs[9]->setScale(3.0);
            dbs[9]->db_fire->setScale(3.0);
            dbs[9]->show_db(0,408,-90,background);
            disconnect(dbs[8],&deerBlaster::fire_finished,0,0);

        });

        for(int i=1;i<=39;i++)
        {
            attacks[i]->setParentItem(battle_frame->battle_frame_in);
            attacks[i]->attackMove(7,200000,move_timer_x,move_timer_y);
        }

        connect(dbs[9],&deerBlaster::fire_finished,this,[=]()
        {
            for(int i=1;i<=39;i++)
            {
                background->removeItem(attacks[i]);
                delete attacks[i];
            }
            for(int i=0;i<=9;i++)
            {
                background->removeItem(dbs[i]);
                delete dbs[i];
            }


            battle_frame->soul->hide();
            battle_frame->expand(110,5);
            connect(battle_frame,&battleFrame::expand_finished,this,[=]()
            {
                if(battle_frame->soul->nowhp>=1) main_interface1->show_text(battle_frame,0);
                connect(main_interface1,&textShower::show_text_finished,this,[=]()
                {
                    is_players_turn=true;
                    fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
                    battle_frame->soul->setPos(32+8,425+13);
                    battle_frame->soul->show();
                    disconnect(battle_frame,&battleFrame::expand_finished,0,0);
                    turn++;
                    disconnect(main_interface1,&textShower::show_text_finished,0,0);
                });
            });

            disconnect(dbs[9],&deerBlaster::fire_finished,0,0);
        });
    }

    /*****************************************************************第二回合*************************************************************************/
    if(turn==2)
    {
        battle_frame->soul->setPos(320,320);
        battle_frame->soul->show();

        QTimer *turn2_timer_1=new QTimer;
        turn2_timer_1->setInterval(5);
        QTimer *turn2_timer_2=new QTimer;
        turn2_timer_2->setInterval(4200);

        attacks.resize(10);
        attacks[1]=new normalAttack(420,280,10,160,battle_frame->soul);
        attacks[2]=new normalAttack(420,280,10,160,battle_frame->soul);
        attacks[3]=new normalAttack(100,90,10,140,battle_frame->soul);
        attacks[4]=new normalAttack(100,90,10,140,battle_frame->soul);
        attacks[5]=new normalAttack(290,480,10,170,battle_frame->soul);
        attacks[6]=new normalAttack(290,480,10,170,battle_frame->soul);
        attacks[7]=new normalAttack(160,600,10,100,battle_frame->soul);
        attacks[8]=new normalAttack(160,600,10,100,battle_frame->soul);

        for(int i=1;i<=8;i++)
            attacks[i]->setPen(Qt::NoPen);


        turn2_timer_1->start();
        turn2_timer_2->start();
        turn2_timer_2->setSingleShot(true);

        connect(turn2_timer_1,&QTimer::timeout,this,[=]()
        {
            attacks[1]->setParentItem(battle_frame->battle_frame_in);
            attacks[2]->setParentItem(battle_frame->battle_frame_in);
            static int angle1=0;
            QPointF op1=attacks[1]->boundingRect().center();
            attacks[1]->setTransformOriginPoint(op1);
            attacks[2]->setTransformOriginPoint(op1);

            attacks[1]->setRotation(angle1);
            attacks[2]->setRotation(angle1+90);
            angle1+=2;
            if(angle1 %10==0)
            {
                attacks[1]->setX(attacks[1]->x()-2);
                attacks[2]->setX(attacks[1]->x()-2);
            }
        });

        connect(turn2_timer_1,&QTimer::timeout,this,[=]()
        {
            attacks[3]->setParentItem(battle_frame->battle_frame_in);
            attacks[4]->setParentItem(battle_frame->battle_frame_in);
            static int angle2=0;
            QPointF op2=attacks[3]->boundingRect().center();
            attacks[3]->setTransformOriginPoint(op2);
            attacks[4]->setTransformOriginPoint(op2);

            attacks[3]->setRotation(angle2);
            attacks[4]->setRotation(angle2+90);
            angle2+=2;
            if(angle2 %10==0)
            {
                if((angle2/2)%2==1)
                {
                    attacks[3]->setPos(attacks[3]->x()+2,attacks[3]->y()+2);
                    attacks[4]->setPos(attacks[4]->x()+2,attacks[4]->y()+2);
                }
                else
                {
                    attacks[3]->setX(attacks[3]->x()+2);
                    attacks[4]->setX(attacks[4]->x()+2);
                }
            }
        });

        connect(turn2_timer_1,&QTimer::timeout,this,[=]()
        {
            attacks[5]->setParentItem(battle_frame->battle_frame_in);
            attacks[6]->setParentItem(battle_frame->battle_frame_in);
            static int angle3=0;
            QPointF op3=attacks[5]->boundingRect().center();
            attacks[5]->setTransformOriginPoint(op3);
            attacks[6]->setTransformOriginPoint(op3);

            attacks[5]->setRotation(angle3);
            attacks[6]->setRotation(angle3+90);
            angle3+=2;
            if(angle3 %10==0)
            {
                attacks[5]->setY(attacks[5]->y()-2);
                attacks[6]->setY(attacks[6]->y()-2);
            }
        });

        connect(turn2_timer_1,&QTimer::timeout,this,[=]()
        {
            attacks[7]->setParentItem(battle_frame->battle_frame_in);
            attacks[8]->setParentItem(battle_frame->battle_frame_in);
            static int angle4=0;
            QPointF op4=attacks[7]->boundingRect().center();
            attacks[7]->setTransformOriginPoint(op4);
            attacks[8]->setTransformOriginPoint(op4);

            attacks[7]->setRotation(angle4);
            attacks[8]->setRotation(angle4+90);
            angle4+=2;
            if(angle4 %10==0)
            {
                if((angle4/2)%2==1)
                {
                    attacks[7]->setPos(attacks[7]->x()+2,attacks[7]->y()-2);
                    attacks[8]->setPos(attacks[8]->x()+2,attacks[8]->y()-2);
                }
                else
                {
                    attacks[7]->setY(attacks[7]->y()-2);
                    attacks[8]->setY(attacks[8]->y()-2);
                }
            }
        });


        connect(turn2_timer_2,&QTimer::timeout,this,[=]()
        {
            gunShoot *shoot1=new gunShoot(battle_frame->soul,background);
            shoot1->setPos(battle_frame->soul->x()-40,battle_frame->soul->y()-40);

            connect(shoot1,&gunShoot::shoot_finished,this,[=]()
            {
                turn2_timer_1->stop();
                background->removeItem(shoot1);
                for(int i=1;i<=8;i++)
                 {
                    background->removeItem(attacks[i]);
                    delete attacks[i];
                 }

                battle_frame->soul->hide();
                battle_frame->expand(110,5);
                connect(battle_frame,&battleFrame::expand_finished,this,[=]()
                {
                    if(battle_frame->soul->nowhp>=1) main_interface1->show_text(battle_frame,0);
                    connect(main_interface1,&textShower::show_text_finished,this,[=]()
                    {
                        is_players_turn=true;
                        fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
                        battle_frame->soul->setPos(32+8,425+13);
                        battle_frame->soul->show();
                        disconnect(battle_frame,&battleFrame::expand_finished,0,0);
                        turn++;
                        disconnect(main_interface1,&textShower::show_text_finished,0,0);
                    });
                });
            });
        });


    }

    /*****************************************************************第三回合*************************************************************************/
    if(turn==3)
    {
        battle_frame->soul->setPos(315,320);
        battle_frame->soul->show();

        QTimer *turn3_timer=new QTimer;
        turn3_timer->start(500);
        static int i=1;
        swords.resize(115);

        connect(turn3_timer,&QTimer::timeout,this,[=]()
        {
            if(i%2==1)
            {
                swords[i]=new Sword(battle_frame->soul,background);
                swords[i]->setPos(145,battle_frame->soul->y()+25);
                swords[i]->setRotation(-90);
                swords[i]->move(50);
            }
            if(i%2==0)
            {
                swords[i]=new Sword(battle_frame->soul,background);
                swords[i]->setPos(500,battle_frame->soul->y()-10);
                swords[i]->setRotation(90);
                swords[i]->move(-50);
            }
            i++;
            if(i==51)///////////////////////////////////////////////////////////////////
            {
                turn3_timer->stop();
                i=1;
                connect(swords[50],&Sword::show_finished,this,[=]//////////////////////////////////////////
                {
                    for(int i=1;i<=50;i++)///////////////////////////////////////////////////////
                    {
                        background->removeItem(swords[i]);
                        delete swords[i];
                    }
                    battle_frame->soul->hide();
                    battle_frame->expand(140,5);
                    connect(battle_frame,&battleFrame::expand_finished,this,[=]()
                    {
                        if(battle_frame->soul->nowhp>=1) main_interface1->show_text(battle_frame,0);
                        connect(main_interface1,&textShower::show_text_finished,this,[=]()
                        {
                            is_players_turn=true;
                            fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
                            battle_frame->soul->setPos(32+8,425+13);
                            battle_frame->soul->show();
                            disconnect(battle_frame,&battleFrame::expand_finished,0,0);
                            turn++;
                            disconnect(main_interface1,&textShower::show_text_finished,0,0);
                        });
                    });
                    disconnect(swords[50],&Sword::show_finished,0,0);
                });
            }
        });

    }

    /*****************************************************************第四回合*************************************************************************/
    if(turn==4)
    {
        battle_frame->soul->setPos(320,340);
        battle_frame->soul->show();

        QGraphicsPixmapItem *axe=new QGraphicsPixmapItem;
        QGraphicsPixmapItem *axe2=new QGraphicsPixmapItem;
        QPixmap pixmap=QPixmap(":/image/image/axe.png");
        QPixmap pixmap2=QPixmap(":/image/image/axe2.png");
        axe->setPixmap(pixmap);
        axe2->setPixmap(pixmap2);
        axe->setPos(287,140);
        axe2->setPos(287,360);
        axe->setScale(2.0);
        axe2->setScale(2.0);
        axe->setTransformOriginPoint(axe->boundingRect().center().x(),axe->boundingRect().center().y()-65);
        axe2->setTransformOriginPoint(axe->boundingRect().center().x(),axe->boundingRect().center().y()+65);
        QGraphicsRectItem *hit_rect=new QGraphicsRectItem(axe->x()-19,axe->y()+180,102,60);
        QGraphicsRectItem *hit_rect2=new QGraphicsRectItem(axe2->x()-17,axe2->y()-105,100,60);
        hit_rect->setTransformOriginPoint(320,140);
        hit_rect2->setTransformOriginPoint(320,490);
        background->addItem(axe);
        background->addItem(hit_rect);
        background->addItem(axe2);
        background->addItem(hit_rect2);

        hit_rect->hide();
        hit_rect2->hide();
        hit_rect->setBrush(Qt::green);
        hit_rect2->setBrush(Qt::green);

        QTimer *update_timer=new QTimer;
        QTimer *rotation_timer=new QTimer;
        update_timer->start(75);
        rotation_timer->start(10);

        connect(update_timer,&QTimer::timeout,this,[=]()
        {
            static bool collide_with_soul=false;
            if(hit_rect->collidesWithItem(battle_frame->soul->hitbox)||hit_rect2->collidesWithItem(battle_frame->soul->hitbox)) collide_with_soul=true;
            else collide_with_soul=false;

            if(collide_with_soul) battle_frame->soul->hurt();
        });

        connect(rotation_timer,&QTimer::timeout,this,[=]()
        {
            static qreal angle=45.5;
            static bool reverse=false;
            axe->setRotation(angle);
            hit_rect->setRotation(angle);
            axe2->setRotation(angle);
            hit_rect2->setRotation(angle);

            if(!reverse) angle+=0.5;
            if(reverse) angle-=0.5;
            if(angle==46||angle==-46) reverse=!reverse;
        });

        QTimer *turn4_timer=new QTimer;
        turn4_timer->setSingleShot(true);
        turn4_timer->start(15000);

        connect(turn4_timer,&QTimer::timeout,this,[=]()
        {
            update_timer->stop();
            rotation_timer->stop();
            background->removeItem(axe);background->removeItem(axe2);background->removeItem(hit_rect);background->removeItem(hit_rect2);
            axe->hide();
            axe2->hide();
            delete axe;delete axe2;delete hit_rect;delete hit_rect2;
        });

        QTimer *turn4_timer_2=new QTimer;
        turn4_timer_2->setSingleShot(true);
        turn4_timer_2->start(15000);

        connect(turn4_timer_2,&QTimer::timeout,this,[=]()
        {
            battle_frame->expand(110,5);
            battle_frame->soul->hide();
            connect(battle_frame,&battleFrame::expand_finished,this,[=]()
            {
                if(battle_frame->soul->nowhp>=1) main_interface1->show_text(battle_frame,0);
                connect(main_interface1,&textShower::show_text_finished,this,[=]()
                {
                    is_players_turn=true;
                    fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
                    battle_frame->soul->setPos(32+8,425+13);
                    battle_frame->soul->show();
                    disconnect(battle_frame,&battleFrame::expand_finished,0,0);
                    turn++;
                    disconnect(main_interface1,&textShower::show_text_finished,0,0);
                });
            });
        });


    }

    /*****************************************************************第五回合*************************************************************************/
    if(turn==5)
    {
        battle_frame->soul->setPos(320,320);
        battle_frame->soul->show();

        QTimer *turn4_timer_1=new QTimer;
        turn4_timer_1->setInterval(500);
        turn4_timer_1->start();

        guns.resize(200);
        attacks.resize(500);
        connect(turn4_timer_1,&QTimer::timeout,this,[=]()
        {
            static int i=0;
            static int j=0;
            guns[i]=new gunShoot(battle_frame->soul,background);
            guns[i]->setPos(battle_frame->soul->x()-32,battle_frame->soul->y()-32);
            i++;
            if(i==10)
            {
                for(int i=0;i<=4;i++)
                for(int k=1;k<=20;k++)
                {
                    attacks[j]=new normalAttack(345+i*10,205+k*10,10,10,battle_frame->soul);
                    attacks[j]->setParentItem(battle_frame->battle_frame_in);
                    j++;
                }
            }
            if(i==20)
            {
                for(int i=0;i<=10;i++)
                for(int k=1;k<=20;k++)
                {
                    attacks[j]=new normalAttack(345-i*10,275+k*10,10,10,battle_frame->soul);
                    attacks[j]->setParentItem(battle_frame->battle_frame_in);
                    j++;
                }
            }
            if(i==30)
            {
                for(int i=0;i<=8;i++)
                for(int k=1;k<=8;k++)
                {
                    attacks[j]=new normalAttack(345-i*10,205+k*10,10,10,battle_frame->soul);
                    attacks[j]->setParentItem(battle_frame->battle_frame_in);
                    j++;
                }
            }
            if(i==41)
            {
                turn4_timer_1->stop();
                for(int k=0;k<=40;k++)
                    delete guns[k];
                for (int k=0;k<=j-1;k++)
                    delete attacks[k];
                i=0;
                j=0;
                QTimer *turn4_timer_2=new QTimer;
                turn4_timer_2->setSingleShot(true);
                turn4_timer_2->start(1000);
                connect(turn4_timer_2,&QTimer::timeout,this,[=]()
                {
                    disconnect(turn4_timer_2,&QTimer::timeout,0,0);
                    delete turn4_timer_2;
                    battle_frame->soul->hide();
                    battle_frame->expand(110,5);
                    connect(battle_frame,&battleFrame::expand_finished,this,[=]()
                    {
                        if(battle_frame->soul->nowhp>=1) main_interface1->show_text(battle_frame,0);
                        connect(main_interface1,&textShower::show_text_finished,this,[=]()
                        {
                            is_players_turn=true;
                            fight->setStyleSheet("QLabel{background-image: url(:/image/image/fight_hover.png);}");
                            battle_frame->soul->setPos(32+8,425+13);
                            battle_frame->soul->show();
                            disconnect(battle_frame,&battleFrame::expand_finished,0,0);
                            turn++;
                            disconnect(main_interface1,&textShower::show_text_finished,0,0);
                        });
                    });
                });
            }
        });
    }

    /*****************************************************************第六回合*************************************************************************/
    if(turn==6)
    {
        battle_frame->soul->setPos(320,320);
        battle_frame->soul->show();
        is_players_turn=false;

        dbs.resize(200);
        QTimer *turn6_timer=new QTimer;


        QTimer *turn6_timer_2=new QTimer;
        turn6_timer_2->start(75);
        connect(turn6_timer_2,&QTimer::timeout,this,[=]
        {
            static int k=1;
            dbs[k]=new deerBlaster(battle_frame->soul,background);
            dbs[k]->show_db(400,50,10*k,background);
            k++;
            if(k==5)
            {
                disconnect(turn6_timer_2,&QTimer::timeout,0,0);
                turn6_timer_2->stop();
                k=1;
            }
        });

        QTimer *turn6_timer_3=new QTimer;
        turn6_timer_3->start(2000);
        turn6_timer_3->setSingleShot(true);
        connect(turn6_timer_3,&QTimer::timeout,this,[=]
        {
            disconnect(turn6_timer_3,&QTimer::timeout,0,0);
            turn6_timer_2->start(75);
            connect(turn6_timer_2,&QTimer::timeout,this,[=]
            {
                static int k=1;
                dbs[k]=new deerBlaster(battle_frame->soul,background);
                dbs[k]->show_db(140,100,-10*k,background);
                k++;
                if(k==5)
                {
                    disconnect(turn6_timer_2,&QTimer::timeout,0,0);
                    turn6_timer_2->stop();
                    k=1;
                }
            });
        });


        QTimer *turn6_timer_4=new QTimer;
        turn6_timer_4->start(4000);
        turn6_timer_4->setSingleShot(true);

        connect(turn6_timer_4,&QTimer::timeout,this,[=]
        {
            disconnect(turn6_timer_4,&QTimer::timeout,0,0);
            turn6_timer_2->start(75);
            connect(turn6_timer_2,&QTimer::timeout,this,[=]
            {
                static int k=1;
                dbs[k]=new deerBlaster(battle_frame->soul,background);
                dbs[k]->show_db(320-32+150*cos(15*(k-1)),240-45+150*sin(15*(k-1)),15*(k-1),background);
                k++;
                if(k==25)
                {
                    disconnect(turn6_timer_2,&QTimer::timeout,0,0);
                    turn6_timer_2->stop();
                    k=1;
                }
            });
        });

        QTimer *turn6_timer_5=new QTimer;
        turn6_timer_5->start(7000);
        turn6_timer_5->setSingleShot(true);
        connect(turn6_timer_5,&QTimer::timeout,this,[=]
        {
            disconnect(turn6_timer_5,&QTimer::timeout,0,0);
            turn6_timer->start(75);
        });

        QTimer *turn6_timer_6=new QTimer;
        turn6_timer_6->setSingleShot(true);


        connect(turn6_timer,&QTimer::timeout,this,[=]
        {
            static int i=1;
            dbs[i]=new deerBlaster(battle_frame->soul,background);
            if(i%24==1)
                dbs[i]->show_db(265,30,0,background);
            if(i%24==2)
                dbs[i]->show_db(340,30,15,background);
            if(i%24==3)
                dbs[i]->show_db(415,45,30,background);
            if(i%24==4)
                dbs[i]->show_db(480,80,45,background);
            if(i%24==5)
                dbs[i]->show_db(535,130,60,background);
            if(i%24==6)
                dbs[i]->show_db(575,190,75,background);
            if(i%24==7)
                dbs[i]->show_db(605,258,90,background);
            if(i%24==8)
                dbs[i]->show_db(610,330,105,background);
            if(i%24==9)
                dbs[i]->show_db(605,405,120,background);
            if(i%24==10)
                dbs[i]->show_db(570,475,135,background);
            if(i%24==11)
                dbs[i]->show_db(520,535,150,background);
            if(i%24==12)
                dbs[i]->show_db(455,580,165,background);
            if(i%24==13)
                dbs[i]->show_db(380,605,180,background);
            if(i%24==14)
                dbs[i]->show_db(300,610,195,background);
            if(i%24==15)
                dbs[i]->show_db(225,590,210,background);
            if(i%24==16)
                dbs[i]->show_db(160,550,225,background);
            if(i%24==17)
                dbs[i]->show_db(100,500,240,background);
            if(i%24==18)
                dbs[i]->show_db(55,440,255,background);
            if(i%24==19)
                dbs[i]->show_db(30,365,270,background);
            if(i%24==20)
                dbs[i]->show_db(35,290,285,background);
            if(i%24==21)
                dbs[i]->show_db(50,220,300,background);
            if(i%24==22)
                dbs[i]->show_db(80,150,315,background);
            if(i%24==23)
                dbs[i]->show_db(125,90,330,background);
            if(i%24==0)
                dbs[i]->show_db(190,50,345,background);
            i++;
            if(i==73+48)
            {
                turn6_timer->stop();
                i=1;
                turn6_timer_6->setSingleShot(true);
                turn6_timer_6->start(3000);

            }
        });


        connect(turn6_timer_6,&QTimer::timeout,this,[=]
        {
            for(int i=1;i<=73+48-1;i++)
                delete dbs[i];
            QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
            QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
            this->setGraphicsEffect(opacity);
            opacityAnimation->setDuration(3000);
            opacityAnimation->setStartValue(1);
            opacityAnimation->setEndValue(0);
            opacityAnimation->start();

            connect(opacityAnimation,&QPropertyAnimation::finished,this,[=]()
            {
                disconnect(opacityAnimation,&QPropertyAnimation::finished,0,0);
                this->setScene(end_scene);
                QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
                QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
                this->setGraphicsEffect(opacity);
                opacityAnimation->setDuration(1);
                opacityAnimation->setStartValue(1);
                opacityAnimation->setEndValue(1);
                opacityAnimation->start();
                end_text->show_text2(230,250,end_scene);

                QTimer *erase_timer=new QTimer;
                erase_timer->start(1500);
                connect(erase_timer,&QTimer::timeout,this,[=]()
                {
                    erase_timer->stop();
                    QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
                    QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
                    this->setGraphicsEffect(opacity);
                    opacityAnimation->setDuration(1000);
                    opacityAnimation->setStartValue(1);
                    opacityAnimation->setEndValue(0);
                    opacityAnimation->start();
                    connect(opacityAnimation,&QPropertyAnimation::finished,this,[=]()
                    {
                        this->close();
                        connect(this,SIGNAL(restart()),this->parentWidget(),SLOT(open_menu()));
                        emit restart();
                    });
                });
            });

            QTimer *fade_timer=new QTimer;
            fade_timer->start(200);
            connect(fade_timer,&QTimer::timeout,this,[=]()
            {
                static int i=1;
                battle_bgm_1->setVolume(0.2-0.01*i);
                i++;
                if(i==21)
                {
                    fade_timer->stop();
                    disconnect(fade_timer,&QTimer::timeout,0,0);
                    i=1;
                    delete fade_timer;
                }
            });
        });
    }
}

