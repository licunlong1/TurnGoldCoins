#ifndef COIN_H
#define COIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QEvent>

class PlayScene;

class Coin : public QPushButton
{
    Q_OBJECT
public:
//    explicit Coin(QWidget *parent = nullptr);
    explicit Coin(QString coin_path,int num,int width,int height,int i,int j,PlayScene *);

    //改变金币的正反面
    void change();

    //改变周围的金币
    void change_around(int num,PlayScene * play);

    //改变所有金币的状态  iswin
    void change_status(int num,PlayScene * play,bool);

    //设置金币的大小 位置 等
    void set_size_pos(QPixmap pix,int num,int width,int height,int i,int j);

    QTimer * timer1 =NULL;//正面变反面
    QTimer * timer2 =NULL;//反面变正面

    //记录图片
    int min = 1;
    int max = 8;

    int posi;
    int posj;
    bool positive;//表示金币的正反面

    bool animalaction = false;//表示金币动画的标志

    bool iswin = false;//判断是否胜利 默认是胜利的

    PlayScene *play_1;

    void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // COIN_H
