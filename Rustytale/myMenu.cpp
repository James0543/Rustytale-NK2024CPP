#include "myMenu.h"

#include<QDebug>


myMenu::myMenu()
{
    //初始化场景
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    s_menu = new QGraphicsScene(this);
    //s_menu->setSceneRect(0, 0, 640, 480);



    //加载菜单界面动画
    movie=new QMovie(":/anime/anime/background.gif");
    label=  new QLabel;
    label->setMaximumSize(640,480);
    label->setMinimumSize(640,480);
    label->setMovie(movie);
    movie->start();
    movie->setSpeed(70);
    s_menu->addWidget(label);



    //初始化按钮,自己写了按钮类，比较方便
    //为什么要手搓？因为我不知道怎么用Designer画场景类的ui(
    start_btn=new gameButton(label);
    start_btn->move(40,200);
    start_btn->setText("开始游戏");
    start_btn->btn_hover();
    s_menu->addWidget(start_btn);

    settings_btn=new gameButton(label);
    settings_btn->move(40,260);
    settings_btn->setText("游戏设置");
    s_menu->addWidget(settings_btn);

    end_btn=new gameButton(label);
    end_btn->move(40,320);
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

}

myMenu::~myMenu()
{
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
}

void myMenu::keyPressEvent(QKeyEvent *k)//相应键盘事件，选择菜单按钮
{
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
        confirm->play();
        switch(hover_btn_index)
        {
            case 1:
            connect(this,SIGNAL(startGame()),this->parentWidget(),SLOT(open_game_wid()));
            emit startGame();
            break;

            case 3:
            connect(this,SIGNAL(endGame()),this->parentWidget(),SLOT(widClose()));
            emit endGame();
            break;
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
    if(cnt==11) {delete timer;}
}
