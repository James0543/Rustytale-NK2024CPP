#include "myMenu.h"

#include<QDebug>


myMenu::myMenu()
{
    setFrameShape(QFrame::NoFrame);

    //初始化场景
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    s_menu = new QGraphicsScene(this);
    s_menu->setSceneRect(0, 0, 640, 480);

    settings =new QGraphicsScene;
    settings->setBackgroundBrush(Qt::black);
    settings->setSceneRect(0, 0, 640, 480);

    //初始化设置按钮
    /*up_key_btn=new QGraphicsTextItem("上：  ↑");
    left_key_btn=new QGraphicsTextItem("左： ←");
    down_key_btn=new QGraphicsTextItem("下： ↓");
    right_key_btn=new QGraphicsTextItem("右： →");
    settings->addItem(up_key_btn);
    settings->addItem(left_key_btn);
    settings->addItem(right_key_btn);
    settings->addItem(down_key_btn);

    up_key_btn->setPos(50,20);
    up_key_btn->setDefaultTextColor(Qt::white);
    up_key_btn->setFont(QFont("fzjcxs",10));

    left_key_btn->setPos(50,50);
    left_key_btn->setDefaultTextColor(Qt::white);
    left_key_btn->setFont(QFont("fzjcxs",10));

    down_key_btn->setPos(50,80);
    down_key_btn->setDefaultTextColor(Qt::white);
    down_key_btn->setFont(QFont("fzjcxs",10));

    right_key_btn->setPos(50,110);
    right_key_btn->setDefaultTextColor(Qt::white);
    right_key_btn->setFont(QFont("fzjcxs",10));*/

    no_settings=new QGraphicsTextItem("作者后面懒得做游戏设置了...");
    no_settings->setFont(QFont("fzxs12",12));
    no_settings->setDefaultTextColor(Qt::white);
    settings->addItem(no_settings);
    no_settings->setPos(20,220);




    //加载菜单界面动画
    movie=new QMovie(":/anime/anime/background.gif");
    label=  new QLabel;
    label->setMaximumSize(640,480);
    label->setMinimumSize(640,480);
    label->setMovie(movie);
    movie->start();
    movie->setSpeed(70);
    s_menu->addWidget(label);



    //初始化按钮
    start_btn=new gameButton(label);
    start_btn->move(60,200+20);
    start_btn->setText("开始游戏");
    start_btn->btn_hover();
    s_menu->addWidget(start_btn);

    settings_btn=new gameButton(label);
    settings_btn->move(60,260+20);
    settings_btn->setText("游戏设置");
    s_menu->addWidget(settings_btn);

    end_btn=new gameButton(label);
    end_btn->move(60,320+20);
    end_btn->setText("退出游戏");
    s_menu->addWidget(end_btn);



    //加载菜单界面bgm
    menu_bgm=new QSoundEffect;
    menu_bgm->setSource(QUrl::fromLocalFile(":/audio/audio/menu_bgm.wav"));
    menu_bgm->setVolume(1.0);
    menu_bgm->play();
    menu_bgm->setLoopCount(999);


    select=new QMediaPlayer;
    select->setMedia(QUrl("qrc:/audio/audio/select.wav"));
    select->setVolume(50);
    confirm=new QMediaPlayer;
    confirm->setMedia(QUrl("qrc:/audio/audio/confirm.wav"));
    confirm->setVolume(50);

    setScene(s_menu);

    battle_fall=new QMediaPlayer;
    battle_fall->setMedia(QUrl("qrc:/audio/audio/battlefall.wav"));
    battle_fall->setVolume(50);
    noise=new QMediaPlayer;
    noise->setMedia(QUrl("qrc:/audio/audio/noise.wav"));
    noise->setVolume(50);



}

myMenu::~myMenu()
{
    /*
    delete this;
    delete movie;
    delete label;
    delete s_menu;
    delete menu_bgm;
    delete start_btn;
    delete settings_btn;
    delete end_btn;
    delete confirm;
    delete select;
    */
    deleteLater();
}


void myMenu::change_size()
{
    if(change_sig)
    {
        this->parentWidget()->showFullScreen();
        this->scale(3,3);
        this->setMaximumSize(640*3,480*3);
        this->setMinimumSize(640*3,480*3);
        this->move(320,0);
        connect(this,SIGNAL(change()),this->parentWidget(),SLOT(expand_g_size()));
        emit change();
        //disconnect(this,SIGNAL(change()),this->parentWidget(),SLOT(change_g_size()));
        //控制全屏
        change_sig=!change_sig;
    }
    else
    {
        this->parentWidget()->showNormal();
        this->scale(0.3333333,0.3333333);
        this->setMaximumSize(640,480);
        this->setMinimumSize(640,480);
        this->move(0,0);
        connect(this,SIGNAL(change()),this->parentWidget(),SLOT(shrink_g_size()));
        emit change();
        //disconnect(this,SIGNAL(change()),this->parentWidget(),SLOT(shrink_g_size()));
        //控制全屏
        change_sig=!change_sig;
    }
}


void myMenu::keyPressEvent(QKeyEvent *k)//相应键盘事件，选择菜单按钮
{
    if(k->key()==Qt::Key_F4)
    {
        change_size();
    }
    if(k->key()==Qt::Key_Down)
    {
        select->play();
        hover_btn_index+=1;
        if(hover_btn_index>=4) hover_btn_index=1;
        switch(hover_btn_index)
        {
            case 1:
            start_btn->btn_hover();
            end_btn->btn_unhover();
            break;

            case 2:
            settings_btn->btn_hover();
            start_btn->btn_unhover();
            break;

            case 3:
            end_btn->btn_hover();
            settings_btn->btn_unhover();
            break;
        }
    }
    if(k->key()==Qt::Key_Up)
    {
        select->play();
        hover_btn_index-=1;
        if(hover_btn_index<=0) hover_btn_index=3;
        switch(hover_btn_index)
        {
            case 1:
            start_btn->btn_hover();
            settings_btn->btn_unhover();
            break;

            case 2:
            settings_btn->btn_hover();
            end_btn->btn_unhover();
            break;

            case 3:
            end_btn->btn_hover();
            start_btn->btn_unhover();
            break;
        }
    }
    if(k->key()==Qt::Key_Z||k->key()==Qt::Key_Return)
    {       
        switch(hover_btn_index)
        {
            case 1:
            battle_fall->play();
            connect(this,SIGNAL(startGame()),this->parentWidget(),SLOT(open_game_wid()));
            emit startGame();
            disconnect(this,SIGNAL(startGame()),this->parentWidget(),SLOT(open_game_wid()));
            break;

            case 2:
            confirm->play();
            if(!is_showing_settings)
            {
                this->setScene(settings);
                is_showing_settings=true;
            }
            break;

            case 3:
            confirm->play();
            connect(this,SIGNAL(endGame()),this->parentWidget(),SLOT(widClose()));
            emit endGame();
            break;
        }
    }
    if(k->key()==Qt::Key_X)
    {
        if(is_showing_settings)
        {
            this->setScene(s_menu);
            is_showing_settings=false;
        }
    }
}

void myMenu::sound_fade_out()
{
    timer=new QTimer;
    timer->setInterval(50);
    //timer->setSingleShot(20);
    connect(timer,SIGNAL(timeout()),this,SLOT(minus_volumn()));
    timer->start();
}

void myMenu::minus_volumn()//音量减小函数
{
    static int cnt=1;
    this->menu_bgm->setVolume(1.0-cnt*0.1);
    cnt+=1;
    if(cnt==11)
    {
        cnt=1;
        disconnect(timer,SIGNAL(timeout()),this,SLOT(minus_volumn()));
        delete timer;
    }
}
