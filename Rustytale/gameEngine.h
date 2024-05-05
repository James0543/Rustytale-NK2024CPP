#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include<QVector>
#include<cmath>
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
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>
#include"gameButton.h"
#include"Soul.h"
#include"battleFrame.h"
#include"normalAttack.h"
#include"targetBar.h"
#include"deerBlaster.h"
#include"textShower.h"
#include"gunShoot.h"
#include"Sword.h"


class gameEngine : public QGraphicsView
{
    Q_OBJECT

public:
    gameEngine();
    ~gameEngine();
    bool change_sig=true;

private:
    //史山
    QGraphicsScene *background;
    QGraphicsScene *fail_scene;
    QGraphicsScene *heart_break_scene;
    QGraphicsScene *end_scene;

    Soul *break_soul;

    bool is_players_turn=0;
    int button_index=1;
    int show_item_index=1;
    int focus_item_index=1;
    int turn=1;
    int item_number=10;

    QLabel *fight;
    QLabel *act;
    QLabel *item;
    QLabel *mercy;

    bool is_fighting=false;
    bool is_showing_target=false;
    bool bar_moving=false;

    bool is_selecting=false;
    bool acted=false;


    bool is_showing_item=false;
    bool is_using_item=false;
    bool used_item=false;
    bool is_mercying=false;


    bool is_dialoging=false;
    bool can_press_key=false;
    bool attacked=false;


    QGraphicsTextItem *lv;
    QGraphicsPixmapItem *hp;
    QGraphicsTextItem *nowhp;
    QGraphicsTextItem *maxhp;


    battleFrame *battle_frame;
    targetBar *bar;
    QGraphicsRectItem *y_healthbar;
    QGraphicsRectItem *r_healthbar;

    QLabel *enemy_lbl;
    QMovie *enemy_gif;
    QPixmap *enemy_pixmap;
    QGraphicsProxyWidget *enemy_wid;
    QGraphicsPixmapItem *dialog_bubble;
    QGraphicsPixmapItem *slice;
    QGraphicsPixmapItem *miss;
    QGraphicsTextItem *debug_mode;

    QTimer *timer;
    QTimer *text_timer;
    QTimer *global_timer;//全局计时器
    QTimer *global_timer2;

    QMediaPlayer *select;
    QMediaPlayer *confirm;
    QMediaPlayer *slice_snd;
    QMediaPlayer *break_snd;
    QMediaPlayer *pieces_snd;

    QMediaPlayer *dia_sound;
    QSoundEffect *battle_bgm_1;
    QSoundEffect *fail_bgm;

    bool failed=false;
    QGraphicsPixmapItem *fail_background;

    struct Item
    {
        QGraphicsTextItem *name;
        textShower *use_msg;
        textShower *describe;
        textShower *heal_msg;
        QString item_name;
        int heal;

        Item(){};
        Item(int h,QString namestr,QString usemessage,QString describestr,QString messagestr,QGraphicsScene *background)
        {  
            item_name=namestr;
            heal=h;
            name =new QGraphicsTextItem(namestr);
            name->setFont(QFont("fzxs12",12));
            name->setDefaultTextColor(Qt::white);
            use_msg = new textShower(usemessage,background);
            describe = new textShower(describestr,background);
            heal_msg = new textShower(messagestr,background);
        }
    }items[15];



    void keyPressEvent(QKeyEvent *k);
    void keyReleaseEvent(QKeyEvent *k);

    void show_dialog(QString str);
    void erase_dialog();
    void player_attack();
    void show_miss();
    void fail();
    void show_item_list(int k);
    void hide_item_list(int k);
    void hide_item_message(int k);
    void use_item(int show,int focus);
    void set_soul_to_item(int index);
    QVector<QGraphicsSimpleTextItem*> dia;//装对话文本的玩意

    QVector<normalAttack*> attacks;
    QVector<deerBlaster*> dbs;
    QVector<Sword*> swords;
    QVector<gunShoot*> guns;


    //文本对象
    textShower *main_interface1;
    textShower *jacob;
    textShower *act_select;
    textShower *introduce;
    textShower *introduce2;
    textShower *end_text;

    int up=0x01000013;
    int left=0x01000012;
    int down=0x01000015;
    int right=0x01000014;

    int v_amend=1;
    bool need_amend=false;


signals:
    void start();
    void change();
    void restart();

public slots:
    void collides_check();
    void battle();
    void change_size();
};

#endif // GAMEENGINE_H
