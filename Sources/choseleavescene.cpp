#include "choseleavescene.h"


ChoseLeaveScene::ChoseLeaveScene(QWidget *parent) : QMainWindow(parent)
{

    //返回音效
    QSound *sound_back = new QSound(":/res/BackButtonSound.wav",this);
    sound_back->setLoops(1);

    //设置选取关卡音效
    QSound *sound_select = new QSound(":/res/TapButtonSound.wav",this);
    sound_select->setLoops(1);



    setFixedSize(400,750);

    setWindowTitle("关卡页面场景");

    setWindowIcon(QIcon(":/res/Coin0001"));

    QMenuBar *menu = new QMenuBar;
    setMenuBar(menu);
    menu->setParent(this);

    QMenu * start_menu = menu->addMenu("开始");

    QAction* quit_action = start_menu->addAction("退出");

    connect(quit_action,&QAction::triggered,[=](){
        this->close();
    });

    MyPushButton* quit_btn = new MyPushButton(":/res/BackButton",":/res/BackButtonSelected");
    quit_btn->setParent(this);
    quit_btn->move(this->width() - quit_btn->width(),this->height() - quit_btn->height());

    connect(quit_btn,&MyPushButton::clicked,this,[=](){
//       qDebug()<<"点击了退出";
        sound_back->play();
        QTimer::singleShot(300,this,[=](){
            emit this->quit_level_scene();
        });
    });

    //这里是错的
//    connect(play_scene,&PlayScene::quit_play_scene,[=](){
//        this->show();
//        delete play_scene;
//        play_scene = NULL;
//    });

    for(int i=0;i<20;i++){
        MyPushButton* level_btn = new MyPushButton(":/res/LevelIcon");
        level_btn->setParent(this);
        level_btn->move(50+i%4*80,150+i/4*80);

        connect(level_btn,&MyPushButton::clicked,[=](){
//            QString str = QString("点击了第 %1 关").arg(i+1);
//            qDebug()<< str;

            sound_select->play();

            //sound_scene->play();
            QTimer::singleShot(300,this,[=](){
                this->hide();
                play_scene = new PlayScene(i+1);
                play_scene->setGeometry(this->geometry());
                play_scene->show();

                connect(play_scene,&PlayScene::quit_play_scene,[=](){
                    //sound_scene->stop();
                    this->setGeometry(play_scene->geometry());
                    this->show();
                    delete play_scene;
                    play_scene = NULL;
                });
            });

        });

        QLabel *label = new QLabel(this);
        label->setParent(this);
        label->setFixedSize(level_btn->width(),level_btn->height());
        label->move(50+i%4*80,150+i/4*80);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setText(QString::number(i+1));

        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}


void ChoseLeaveScene::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title");
    painter.drawPixmap(this->width() * 0.5 - pix.width() * 0.5,30,pix.width(),pix.height(),pix);

}
