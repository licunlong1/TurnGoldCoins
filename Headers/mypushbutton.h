#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QDebug>
#include <QPushButton>
#include <QPropertyAnimation>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
    explicit MyPushButton(QString normalPath,QString pressPath = "");

    QString normalImg;
    QString pressImg;

    //设置开始按钮的动画
    void zoom(bool flag);

    //设置退出按钮的动画
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
