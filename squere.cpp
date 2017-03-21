#include "squere.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

//#include <QDebug>

Squere::Squere(QWidget *parent,struct SETTINGS *settings):QWidget(parent)
{
    setFixedSize(settings->squere_width,settings->squere_height);
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    QLabel *label = new QLabel;
    lay->addWidget(label);
    label->setFixedSize(settings->squere_width,settings->squere_height);
    desc.bottom = true;
    desc.top = true;
    desc.left = true;
    desc.right = true;
    desc.clicked = false;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),SLOT(timeOut()));
    koeff = 0;
    this->settings = settings;
}

void Squere::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int width = settings->squere_width;
    int height = settings->squere_height;
    QBrush brush(desc.clicked?settings->color_act:settings->color_default, Qt::SolidPattern);
    if (!koeff)
        painter.fillRect(QRect(0,0,width,height),brush);
    else
        painter.fillRect(QRect(width/2-width*koeff/20,height/2-height*koeff/20,width*koeff/10,height*koeff/10),brush);
    painter.setPen(QPen(desc.top?settings->color_border:settings->color_act,settings->border_width/2,Qt::SolidLine));
    painter.drawLine(QPoint(0,0),QPoint(width,0));
    painter.setPen(QPen(desc.left?settings->color_border:settings->color_act,settings->border_width/2,Qt::SolidLine));
    painter.drawLine(QPoint(0,0),QPoint(0,height));
    painter.setPen(QPen(desc.bottom?settings->color_border:settings->color_act,settings->border_width/2,Qt::SolidLine));
    painter.drawLine(QPoint(0,height),QPoint(width,height));
    painter.setPen(QPen(desc.right?settings->color_border:settings->color_act,settings->border_width/2,Qt::SolidLine));
    painter.drawLine(QPoint(width,0),QPoint(width,height));
}

void Squere::mousePressEvent(QMouseEvent *event){
//    qDebug()<<event->globalPos()<<mapToGlobal(geometry().topLeft());
    if (event->button() == Qt::LeftButton){
        emit clicked(objectName());
        event->accept();
    }
}

void Squere::changeDescription(int pos, bool state){
    switch (pos) {
    case CLICKED:
        desc.clicked = !desc.clicked;
        if (!timer->isActive())timer->start(15);
        break;
    case TOP:
        desc.top = !desc.top;
        break;
    case BOTTOM:
        desc.bottom = !desc.bottom;
        break;
    case LEFT:
        desc.left = !desc.left;
        break;
    case RIGHT:
        desc.right = !desc.right;
        break;
    }
}

bool Squere::getDeskClicked(){
    return desc.clicked;
}


void Squere::timeOut(){
    if (desc.clicked){
        if (++koeff==10) {
            timer->stop();
        }
    }
    else{
        if (--koeff==0) {
            timer->stop();
        }
    }
    repaint();
}
