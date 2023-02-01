#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include <QVector>
#include <QDebug>
#include <QPixmap>
#include <QSound>
#include <QPropertyAnimation>
#include <QKeyEvent>
#include "dataconfig.h"
#include "mainwindow.h"


#include "mypushbutton.h"
//#include "choseleavescene.h"
//#include "coin.h"

class Coin;
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    explicit PlayScene(int level_num);

    //绘画事件
    void paintEvent(QPaintEvent *event);

    QVector<QVector<int>> array;

    QVector<QVector<Coin*>> array_coin;

    bool iswin = true;//判断是否胜利 默认是胜利的
    bool flag;//判断是否胜利 默认是胜利的

    //判断是否胜利
    void is_win(int num);

    //加载胜利的图片
    QLabel *success_lab = NULL;

    //弹出胜利图片
    void jump_success_img();

    //键盘按下事件
    void keyPressEvent(QKeyEvent *event);
    bool event(QKeyEvent *event);

    bool eventFilter(QObject *watched, QKeyEvent *event);

signals:
    void quit_play_scene();

};

#endif // PLAYSCENE_H
