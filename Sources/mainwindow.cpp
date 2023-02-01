#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choseleavescene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置音效
    QSound *youxi = new QSound(":/res/myDouDZ.wav",this);
    youxi->setLoops(-1);
    youxi->play();

    //设置音效
    QSound *sound_start = new QSound(":/res/TapButtonSound.wav",this);
    sound_start->setLoops(1);


    //设置关卡界面音效
    sound_scene = new QSound(":/res/LevelWinSound.wav",this);
    sound_scene->setLoops(1);

    //设置窗口固定大小
    this->setFixedSize(400,750);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001"));

    //设置窗口名称
    this->setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    MyPushButton* start_btn = new MyPushButton(":/res/MenuSceneStartButton");
    start_btn->setParent(this);
    start_btn->move(this->width() * 0.5 - start_btn->width() * 0.5,this->height() * 0.7);

    choseleave = new ChoseLeaveScene;

    connect(choseleave,&ChoseLeaveScene::quit_level_scene,[=](){
        youxi->play();
        this->show();
        //sound_scene->stop();
        this->setGeometry(choseleave->geometry());
        choseleave->setAttribute(Qt::WA_DeleteOnClose);
        choseleave->hide();
    });


    connect(start_btn,&MyPushButton::clicked,[=](){

        sound_start->play();
        //youxi->stop();
        //sound_scene->play();
//        qDebug()<<"点击了开始";

        start_btn->zoom(true);
        start_btn->zoom(false);

        QTimer::singleShot(200,this,[=](){
            choseleave->setGeometry(this->geometry());
            this->hide();

            choseleave->show();
        });

    });

}


void MainWindow::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPixmap img;
    img.load(":/res/PlayLevelSceneBg");

    painter.drawPixmap(0,0,this->width(),this->height(),img);

    img.load(":/res/Title");
    img = img.scaled(img.width()*0.5,img.height()*0.5);
    painter.drawPixmap(10,30,img);

}

MainWindow::~MainWindow()
{
    delete ui;
}
