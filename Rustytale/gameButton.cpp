#include "gameButton.h"

gameButton::gameButton()
{
    this->btn_unhover();
}

gameButton::gameButton(QWidget* parent)
{
    this->btn_unhover();
    this->setParent(parent);
}

void gameButton::btn_unhover()
{
    QFile file_btn_style(":/style_sheet/style/btn_style_sheet.qss");
    file_btn_style.open(QFile::ReadOnly);
    QString btn_style;
    if(file_btn_style.isOpen())
    {
        btn_style=QLatin1String(file_btn_style.readAll());
        file_btn_style.close();
    }
    this->setStyleSheet(btn_style);
}

void gameButton::btn_hover()
{
    QFile file_btn_style2(":/style_sheet/style/btn_style_sheet2.qss");
    file_btn_style2.open(QFile::ReadOnly);
    QString btn_style2;
    if(file_btn_style2.isOpen())
    {
        btn_style2=QLatin1String(file_btn_style2.readAll());
        file_btn_style2.close();
    }
    this->setStyleSheet(btn_style2);
}

gameButton::~gameButton()
{
    deleteLater();
}
