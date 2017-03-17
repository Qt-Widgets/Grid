#include "squere.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
//#include <QDebug>

Squere::Squere(QWidget *parent):QWidget(parent)
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
}

void Squere::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush(desc.clicked?Qt::green:Qt::gray, Qt::SolidPattern);
    painter.fillRect(QRect(0,0,32,32),brush);
    painter.setPen(QPen(desc.top?Qt::black:Qt::green,0.5,Qt::SolidLine));
    painter.drawLine(QPoint(0,0),QPoint(SIZE,0));
    painter.setPen(QPen(desc.left?Qt::black:Qt::green,0.5,Qt::SolidLine));
    painter.drawLine(QPoint(0,0),QPoint(0,SIZE));
    painter.setPen(QPen(desc.bottom?Qt::black:Qt::green,0.5,Qt::SolidLine));
    painter.drawLine(QPoint(0,SIZE),QPoint(SIZE,SIZE));
    painter.setPen(QPen(desc.right?Qt::black:Qt::green,0.5,Qt::SolidLine));
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
    repaint();
}
