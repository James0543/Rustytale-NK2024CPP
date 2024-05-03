#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QLabel>
#include<QFile>
#include<QSoundEffect>

class gameButton : public QLabel
{
public:
    gameButton();
    ~gameButton();
    gameButton(QWidget *parent);

    void btn_hover();
    void btn_unhover();

};

#endif // GAMEBUTTON_H
