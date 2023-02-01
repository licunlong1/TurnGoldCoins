#ifndef CHOSELEAVESCENE_H
#define CHOSELEAVESCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

#include "playscene.h"
#include "mypushbutton.h"

class ChoseLeaveScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoseLeaveScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    PlayScene* play_scene = NULL;


signals:
    void quit_level_scene();

};

#endif // CHOSELEAVESCENE_H
