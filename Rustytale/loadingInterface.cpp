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
    delete menu;
    delete game_engine;
    delete t;
    delete sound;
}

void loadingInterface::init_menu()
{
    menu=new myMenu();
    menu->setParent(this);
    menu->setMaximumSize(640,480);
    menu->setMinimumSize(640,480);
}

void loadingInterface::init_engine()
{
    game_engine=new gameEngine();
    game_engine->setParent(this);
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
    if(k->key()==Qt::Key_Z||k->key()==Qt::Key_Return)
    {
        delete background_image;
        init_menu();
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
    init_engine();
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
