#ifndef LOADINGINTERFACE_H
#define LOADINGINTERFACE_H

#include <QMainWindow>
#include<QLabel>
#include<QPixmap>
#include<QKeyEvent>
#include<QTimer>
#include<QSoundEffect>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QPropertyAnimation>
#include "myMenu.h"
#include<gameEngine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class loadingInterface; }
QT_END_NAMESPACE

class loadingInterface : public QMainWindow
{
    Q_OBJECT

public:
    loadingInterface(QWidget *parent = nullptr);
    ~loadingInterface();


private:
    Ui::loadingInterface *ui;
    void keyPressEvent(QKeyEvent *k);
    void init_menu();
    void init_engine();

    QTimer *t;
    myMenu* menu;
    gameEngine *game_engine;
    QSoundEffect* sound;
    QPropertyAnimation *ani_cut;
    QLabel *background_image;

signals:
    void start_title();

private slots:
    void showTitle();
    void widClose();
    void open_game_wid();


};
#endif // LOADINGINTERFACE_H
