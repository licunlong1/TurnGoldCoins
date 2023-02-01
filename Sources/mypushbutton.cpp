#include "mypushbutton.h"

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
MyPushButton::MyPushButton(QString normalPath,QString pressPath){
    this->normalImg = normalPath;
    this->pressImg = pressPath;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }

    //设置按钮固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置按钮图标
    this->setIcon(QIcon(pix));

    //设置按钮图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

    //设置图标样式 无边框
    this->setStyleSheet("QPushButton{border:0px;}");

}

//动画1
void MyPushButton::zoom(bool flag){
    QPropertyAnimation* ani = new QPropertyAnimation(this,"geometry");

    //设置间隔时间
    ani->setDuration(200);

    if(flag){
        //设置开始的动画
        ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

        //设置结束的动画
        ani->setEndValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));
    }else{
        //设置开始的动画
        ani->setStartValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));

        //设置结束的动画
        ani->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    }

    //设置跳的动画
    ani->setEasingCurve(QEasingCurve::OutBounce);

    //开始动画
    ani->start();
}


void MyPushButton::mousePressEvent(QMouseEvent *e){
//    qDebug()<<this->pressImg;
//    qDebug()<<this->normalImg;
    if(this->pressImg != ""){

        QPixmap pix;
        bool ret = pix.load(this->pressImg);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        setIcon(QIcon(pix));

        setIconSize(QSize(pix.width(),pix.height()));

        this->setStyleSheet("QPushButton{border:0px;}");
    }

    return QPushButton::mousePressEvent(e);
}


void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
//    qDebug()<<this->pressImg;
//    qDebug()<<this->normalImg;
    if(this->pressImg != ""){

        QPixmap pix;
        bool ret = pix.load(this->normalImg);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());

        setIcon(QIcon(pix));

        setIconSize(QSize(pix.width(),pix.height()));

        this->setStyleSheet("QPushButton{border:0px;}");
    }

    return QPushButton::mouseReleaseEvent(e);
}
