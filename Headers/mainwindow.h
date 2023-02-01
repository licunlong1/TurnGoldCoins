#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QPicture>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QSound>

#include "mypushbutton.h"
class ChoseLeaveScene;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);

    ChoseLeaveScene * choseleave = NULL;

    //设置关卡界面音效
    QSound *sound_scene = NULL;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
