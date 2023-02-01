#include "playscene.h"
#include "dataconfig.h"
#include "coin.h"
#include "mypushbutton.h"

PlayScene::PlayScene(int level_num){

    installEventFilter(this);

    //设置点击金币音效
    QSound *sound_click_coin = new QSound(":/res/ConFlipSound.wav",this);
    sound_click_coin->setLoops(1);

    //返回音效
    QSound *sound_back = new QSound(":/res/BackButtonSound.wav",this);
    sound_back->setLoops(1);

    this->flag = true;

    setFixedSize(400,750);

    setWindowTitle("游戏页面场景");

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
        sound_back->play();
//      qDebug()<<"点击了退出";
        QTimer::singleShot(300,this,[=](){
            emit this->quit_play_scene();
        });
    });

    //加载胜利的图片
    success_lab = new QLabel(this);
    QPixmap pix(":/res/LevelCompletedDialogBg");
    success_lab->setFixedSize(pix.width(),pix.height());
    success_lab->setPixmap(pix);
    success_lab->move((this->width() - pix.width()) / 2 ,-pix.height());
    success_lab->setStyleSheet("QPushButton{border:0px;}");



    QLabel* lab = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str = QString("Level: %1").arg(level_num);
    lab->setFont(font);
    lab->setText(str);
    lab->setGeometry(30,this->height() - 50,130,50);
    //lab->move(30,this->height() - 30);

    //设置关卡的难度
    int num;
    if(level_num <= 10){
        num = 4;
    }else if(level_num > 10 && level_num <= 15){
        num = 5;
    }else{
        num = 6;
    }



    array.clear();
    array_coin.clear();

    dataConfig data;
    for(int i = 0 ;i < num;i++){
        QVector<int> v1;
        for(int j = 0;j < num;j++){
            v1.push_back(data.mData[level_num][i][j]);
        }
        array.push_back(v1);
    }

    for(int i = 0 ;i < num;i++){
        QVector<Coin*> array_coin1;
        for(int j = 0;j < num;j++){
            QPixmap pix(":/res/BoardNode");
            QLabel* bg_lab = new QLabel(this);
            bg_lab->setFixedSize(pix.width(),pix.height());
            bg_lab->setPixmap(pix);
            bg_lab->setGeometry(0,0,pix.width(),pix.height());
            bg_lab->move((this->width() - pix.width() * num)/2 + i * pix.width(),
                         (this->height() - pix.height() * num)/2 + j * pix.height() );
            QString str;
            if(array[i][j] == 1){
                str = ":/res/Coin0001";
            }else{
                str = ":/res/Coin0008";
            }

            Coin * coin = new Coin(str,num,this->width(),this->height(),i,j,this);
            coin->posi = i;
            coin->posj = j;
            //记录每个创建出来的金币
            array_coin1.push_back(coin);
            //正面代表true 反面代表false  true 1 金币  false 0 银币
            coin->positive = array[i][j];
            coin->setParent(this);
            connect(coin,&Coin::clicked,[=](){

                sound_click_coin->play();
                this->array_coin[i][j]->change_status(num,this,true);

                //翻转金币
                qDebug()<<"开始翻转金币";
                coin->change();

                //翻转周围的金币
                coin->change_around(num,this);

//                QTimer *time = new QTimer(this);
//                time->start(200);
//                connect(time,&QTimer::timeout,[=](){
//                    this->array_coin[i][j]->change_status(num,this,false);
//                });


                //创建定时任务
                QTimer *success_time = new QTimer(this);
                success_time->start(200);
                connect(success_time,&QTimer::timeout,[=](){

                    this->iswin = true;
                    this->is_win(num);
                    this->array_coin[i][j]->change_status(num,this,false);

                    if(this->iswin){
                        qDebug()<<"胜利了--------";
                        //改变按钮的状态位不可选中 点击
                        this->array_coin[i][j]->change_status(num,this,true);
                        this->jump_success_img();
                        success_time->stop();
                    }
                });
            });

        }
        array_coin.push_back(array_coin1);
    }

    //测试数据
//    for(int i = 0 ;i < num;i++){

//        for(int j = 0;j < num;j++){
//            qDebug()<<array[i][j];
//        }
//        qDebug()<<"";
//    }

}




void PlayScene::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title");
    painter.drawPixmap(this->width() * 0.5 - pix.width() * 0.5,30,pix.width(),pix.height(),pix);

}

void PlayScene::is_win(int num){
    for(int i = 0 ;i < num;i++){

        for(int j = 0;j < num;j++){
            if(array_coin[i][j]->positive == false){
                this->iswin = false;
                break;
            }
        }

    }
}

//弹出胜利图片
void PlayScene::jump_success_img(){

    QPropertyAnimation * ani = new QPropertyAnimation(this->success_lab,"geometry");

    ani->setCurrentTime(1000);

    ani->setStartValue(QRect(this->success_lab->x(),this->success_lab->y(),
                             this->success_lab->width(),this->success_lab->height()));

    ani->setEndValue(QRect(this->success_lab->x(),this->success_lab->y() + 114,
                             this->success_lab->width(),this->success_lab->height()));

    ani->setEasingCurve(QEasingCurve::OutBounce);

    ani->start();

}


void PlayScene::keyPressEvent(QKeyEvent *event){
    qDebug()<<event->key();
//    qDebug()<<Qt::Key_Q;
//    if(event->key() == Qt::Key_Q){
//        qDebug()<<"按下了空格";
//        return;
//    }
    if(event->key() == Qt::Key_Space){
        qDebug()<<"按下了空格";
        return;
    }
}


bool PlayScene::event(QKeyEvent *event){

    if(event->key() == Qt::Key_Q){
        qDebug()<<"按下了空格";
        return true;
    }
}

bool PlayScene::eventFilter(QObject *watched, QKeyEvent *event){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(watched == this->array_coin[i][j]){
                if(event->key() == Qt::Key_Space){
                    qDebug()<<"按下了空格";
                    return true;
                }
            }
        }
    }


    return QMainWindow::eventFilter(watched,event);
}
