#include "loadingInterface.h"
#include "ui_loadingInterface.h"



#include<QDebug>

loadingInterface::loadingInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loadingInterface)
{

    ui->setupUi(this);
    this->setWindowTitle("Rustytale");
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    this->setStyleSheet("background-color: rgb(0, 0, 0)");


    t=new QTimer(this);
    t->setSingleShot(true);
    connect(t,SIGNAL(timeout()),this,SLOT(showTitle()));
    t->start(600);
    //计时器，延迟显示标题界面

    background_image=new QLabel(this);
    QPixmap pixmap=QPixmap(":/image/image/title.png");
    background_image->setPixmap(pixmap);
    background_image->setMaximumSize(640,480);
    background_image->setMinimumSize(640,480);
    background_image->show();
}

loadingInterface::~loadingInterface()
{
    /*
    delete menu;
    delete game_engine;
    delete t;
    delete sound;
    */
    deleteLater();
}

void loadingInterface::init_menu()
{
    menu=new myMenu();
    menu_init_ed=true;
    menu->setMaximumSize(640,480);
    menu->setMinimumSize(640,480);
}

void loadingInterface::init_engine()
{
    game_engine=new gameEngine();
    engine_init_ed=true;
    game_engine->setMaximumSize(640,480);
    game_engine->setMinimumSize(640,480);
}



void loadingInterface::showTitle()
{
    sound=new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile(":/audio/audio/pumpumpum.wav"));
    sound->setVolume(20);
    sound->play();

    this->setWindowTitle("Rustytale");
    //qDebug()<<"ok2";
}

void loadingInterface::keyPressEvent(QKeyEvent *k)
{
    if(k->key()==Qt::Key_F4)
    {
        static bool change_sig=true;
        if(change_sig)
        {
            //background_image=new QLabel(this);
            QPixmap pixmap=QPixmap(":/image/image/title_fullscreen.png");
            background_image->setPixmap(pixmap);
            background_image->setMaximumSize(640*3,480*3);
            background_image->setMinimumSize(640*3,480*3);
            background_image->move(320,0);
            this->showFullScreen();
            change_engine_size=true;
            change_menu_size=true;
            change_sig=!change_sig;
        }
        else
        {
            //background_image=new QLabel(this);
            QPixmap pixmap=QPixmap(":/image/image/title.png");
            background_image->setPixmap(pixmap);
            background_image->setMaximumSize(640,480);
            background_image->setMinimumSize(640,480);
            background_image->move(0,0);
            this->showNormal();
            this->resize(640,480);
            change_engine_size=false;
            change_menu_size=false;
            change_sig=!change_sig;
        }

    }
    if(k->key()==Qt::Key_Z||k->key()==Qt::Key_Return)
    {
        background_image->hide();
        init_menu();
        menu->setParent(this);
        if(change_menu_size) menu->change_size();
        QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
        QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
        menu->setGraphicsEffect(opacity);
        opacityAnimation->setDuration(100);
        opacityAnimation->setStartValue(0);
        opacityAnimation->setEndValue(1);
        opacityAnimation->start();
        menu->show();
        menu->setFocus();
        //qDebug()<<"ok";
    }
}

void loadingInterface::widClose()
{
    this->close();
}

void loadingInterface::open_game_wid()
{
    init_engine();//看看要不要加标志变量
    game_engine->setParent(this);
    if(change_engine_size) game_engine->change_size();
    menu->sound_fade_out();
    menu->hide();
    game_engine->show();
    game_engine->setFocus();
    QGraphicsOpacityEffect *opacity=new QGraphicsOpacityEffect;
    QPropertyAnimation *opacityAnimation=new QPropertyAnimation(opacity,"opacity");
    game_engine->setGraphicsEffect(opacity);
    opacityAnimation->setDuration(1000);
    opacityAnimation->setStartValue(0);
    opacityAnimation->setEndValue(1);
    opacityAnimation->start();
}

void loadingInterface::open_menu()
{
    menu->show();
    menu->menu_bgm->stop();
    menu->menu_bgm->play();
    menu->menu_bgm->setVolume(1.0);
    menu->setFocus();
    if(!game_engine->change_sig&&menu->change_sig)
    {
        menu->scale(3,3);
        menu->setMaximumSize(640*3,480*3);
        menu->setMinimumSize(640*3,480*3);
        menu->move(320,0);
        menu->change_sig=false;
        change_engine_size=true;
    }
}


void loadingInterface::expand_g_size()
{
    change_engine_size=true;
}

void loadingInterface::shrink_g_size()
{
    change_engine_size=false;
}
