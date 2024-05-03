#ifndef MYMENU_H
#define MYMENU_H

#include<QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include<QMovie>
#include<QSoundEffect>
#include<QLabel>
#include<QPushButton>
#include<QFile>
#include<QString>
#include<QTimer>
#include<QMediaPlayer>
#include"gameButton.h"
#include "gameEngine.h"

class myMenu : public QGraphicsView
{
    Q_OBJECT

public:
    myMenu();
    ~myMenu();
    QSoundEffect *menu_bgm;

    QMediaPlayer *select;
    QMediaPlayer *confirm;
    QTimer *timer;
    void sound_fade_out();
    QMediaPlayer *battle_fall;
    QMediaPlayer *noise;

    bool change_sig=true;


signals:
    void startGame();
    void open_settings();
    void endGame();
    void change();

private:   
    int hover_btn_index=1;

    QGraphicsScene *s_menu;
    QLabel *label;
    QMovie *movie;


    gameButton *start_btn;
    gameButton *settings_btn;
    gameButton *end_btn;
    //这里以后加点东西,存档什么的

    void keyPressEvent(QKeyEvent *k);

public slots:
    void minus_volumn();
    void change_size();
};

#endif // MYMENU_H
