#include "coin.h"
#include "playscene.h"
//Coin::Coin(QWidget *parent) : QPushButton(parent)
//{

//}


Coin::Coin(QString coin_path,int num,int width,int height,int i,int j,PlayScene * play){

    QPixmap pix(coin_path);

    this->set_size_pos(pix,num,width,height,i,j);

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        QPixmap pix;
        bool ret = pix.load(str);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        this->set_size_pos(pix,num,width,height,i,j);

        if(this->min > this->max){
            this->min = 1;
            play->array[i][j] = play->array[i][j] == 1 ? 0 : 1;
            qDebug()<<play->array[i][j];
            timer1->stop();
            this->animalaction = false;
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        QPixmap pix;
        bool ret = pix.load(str);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        this->set_size_pos(pix,num,width,height,i,j);
        if(this->max < this->min){
            this->max = 8;
            play->array[i][j] = play->array[i][j] == 1 ? 0 : 1;
            qDebug()<<play->array[i][j];
            timer2->stop();
            this->animalaction = false;
        }
    });

}


void Coin::change(){
    if(this->positive){
        //金币变银币
        timer1->start(40);
        this->animalaction = true;
        this->positive = false;
    }else{
        //银币变金币
        timer2->start(40);
        this->animalaction = true;
        this->positive = true;
    }
}


void Coin::change_around(int num,PlayScene * play){
    int pos_i[4] = {1,0,0,-1};
    int pos_j[4] = {0,-1,1,0};
    for(int i = 0;i < 4;i++){
        int x = this->posi + pos_i[i];
        int y = this->posj + pos_j[i];
        if(x >= 0 && x < num && y >= 0 && y < num){
            QTimer::singleShot(200,this,[=](){
                play->array_coin[x][y]->change();
            });
        }
    }

}

void Coin::change_status(int num,PlayScene * play,bool flag){
    for(int i = 0 ;i < num;i++){

        for(int j = 0;j < num;j++){
            play->array_coin[i][j]->iswin = flag;
        }

    }
}


void Coin::set_size_pos(QPixmap pix,int num,int width,int height,int i,int j){

    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->move((width - (pix.width()+4) * num)/2 + i * (pix.width()+4) + 2 ,
               (height - (pix.height()+6) * num)/2 + j * (pix.height()+6) + 2);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px;}");
}

//鼠标点击事件
void Coin::mousePressEvent(QMouseEvent *e){
    if(this->animalaction || this->iswin){
        return;
    }else{
        return QPushButton::mousePressEvent(e);
    }
}
