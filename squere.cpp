#include "squere.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
//#include <QDebug>

Squere::Squere(QWidget *parent,struct SETTINGS *settings):QWidget(parent)
{
    setFixedSize(SIZE,SIZE);
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    QLabel *label = new QLabel;
    lay->addWidget(label);
    label->setFixedSize(SIZE,SIZE);
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

    QBrush brush(desc.clicked?settings->color_act:settings->color_default, Qt::SolidPattern);
    if (!koeff)
        painter.fillRect(QRect(0,0,SIZE,SIZE),brush);
    else
        painter.fillRect(QRect(SIZE/2-SIZE*koeff/20,SIZE/2-SIZE*koeff/20,SIZE*koeff/10,SIZE*koeff/10),brush);
    painter.setPen(QPen(desc.top?settings->color_border:settings->color_act,0.5,Qt::SolidLine));
    painter.drawLine(QPoint(0,0),QPoint(SIZE,0));
    painter.setPen(QPen(desc.left?settings->color_border:settings->color_act,0.5,Qt::SolidLine));
    painter.drawLine(QPoint(0,0),QPoint(0,SIZE));
    painter.setPen(QPen(desc.bottom?settings->color_border:settings->color_act,0.5,Qt::SolidLine));
    painter.drawLine(QPoint(0,SIZE),QPoint(SIZE,SIZE));
    painter.setPen(QPen(desc.right?settings->color_border:settings->color_act,0.5,Qt::SolidLine));
    painter.drawLine(QPoint(SIZE,0),QPoint(SIZE,SIZE));
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
