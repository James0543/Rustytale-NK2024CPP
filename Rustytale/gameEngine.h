#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include<QVector>

#include<QKeyEvent>
#include<QPaintEvent>
#include<QPainter>
#include<QFont>
#include<QFontDatabase>
#include<QLabel>
#include<QTimer>
#include<QElapsedTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include<QGraphicsProxyWidget>
#include<QObject>
#include<QSoundEffect>
#include<QMovie>
#include<QMediaPlayer>
#include"gameButton.h"
#include"Soul.h"
#include"battleFrame.h"
#include"normalAttack.h"
class gameEngine : public QGraphicsView
{
    Q_OBJECT

public:
    gameEngine();
    ~gameEngine();

private:
    QGraphicsScene *background;
    bool is_players_turn=0;

    QLabel *fight;
    QLabel *act;
    QLabel *item;
    QLabel *mercy;

    bool is_fighting=false;
    bool is_acting=false;
    bool  is_iteming=false;
    bool is_mercying=false;
    bool is_dialoging=false;

    QGraphicsTextItem *lv;
    QGraphicsTextItem *hp;
    QGraphicsTextItem *nowhp;
    QGraphicsTextItem *maxhp;


    battleFrame *battle_frame;
    QGraphicsRectItem *y_healthbar;
    QGraphicsRectItem *r_healthbar;

    QLabel *enemy_lbl;
    QMovie *enemy_gif;
    QPixmap *enemy_pixmap;
    QGraphicsPixmapItem *dialog_bubble_1;
    QGraphicsPixmapItem *dialog_bubble_2;

    QTimer *timer;
    QTimer *global_timer;//全局计时器
    QTimer *global_timer2;

    QMediaPlayer *select;
    QMediaPlayer *confirm;
    QMediaPlayer *text;
    QSoundEffect *battle_bgm_1;

    int button_index=1;
    int turn=1;

    void keyPressEvent(QKeyEvent *k);
    void keyReleaseEvent(QKeyEvent *k);

    void show_text(QString str);
    void show_dialog(QString str);
    void erase_text();
    void erase_dialog();
    QVector<QGraphicsSimpleTextItem*> v;//装界面文本的玩意
    QVector<QGraphicsSimpleTextItem*> dia;//装对话文本的玩意

    QVector<normalAttack*> attacks;

signals:
    void start();
    void show_text_finished();

private slots:
    void collides_check();
    void battle();
};

#endif // GAMEENGINE_H
