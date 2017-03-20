#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "squere.h"
#include "QScreen"
#include "QHBoxLayout"
#include "QLabel"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lay = new QGridLayout();
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    lay->setColumnMinimumWidth(0,SIZE);
    ui->centralWidget->setLayout(lay);
    QRect n = QApplication::screens().first()->availableGeometry();
    num_row = n.height()/SIZE;
    num_col = n.width()/SIZE;
    for (int i = 0; i<num_row;i++){
        for (int j = 0; j<num_col; j++){
            Squere *s = new Squere(this);
            s->setObjectName(QString("%1:%2").arg(i).arg(j));
            lay->addWidget(s,i,j,1,1,Qt::AlignCenter);
            connect(s,SIGNAL(clicked(QString)),SLOT(clickSquere(QString)));
        }
    }
    history_list = new QStringList();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete history_list;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key()==Qt::Key_Z&&event->modifiers()==Qt::ControlModifier){
        if (history_list->isEmpty())return;
        clickSquere(history_list->last());
        history_list->removeLast();
        history_list->removeLast();
    }
}


void MainWindow::clickSquere(QString name_obj){
    QStringList list = name_obj.split(':');
    history_list->append(name_obj);
    int row = list.first().toInt();
    int column = list.last().toInt();
    Squere *s = this->findChild<Squere*>(name_obj);
    s->changeDescription(CLICKED,true);
    Squere *sn = NULL;    
    if (column){
        sn = this->findChild<Squere*>(QString("%1:%2").arg(row).arg(column-1));
        if (sn->getDeskClicked()){
            sn->changeDescription(RIGHT,true);
            s->changeDescription(LEFT,true);
        }
    }
    if (column<num_col-1){
        sn = this->findChild<Squere*>(QString("%1:%2").arg(row).arg(column+1));
        if (sn->getDeskClicked()){
            sn->changeDescription(LEFT,true);
            s->changeDescription(RIGHT,true);
        }
    }
    if (row){
        sn = this->findChild<Squere*>(QString("%1:%2").arg(row-1).arg(column));
        if (sn->getDeskClicked()){
            sn->changeDescription(BOTTOM,true);
            s->changeDescription(TOP,true);
        }
    }
    if (row<num_row-1){
        sn = this->findChild<Squere*>(QString("%1:%2").arg(row+1).arg(column));
        if (sn->getDeskClicked()){
            sn->changeDescription(TOP,true);
            s->changeDescription(BOTTOM,true);
        }
    }
    repaint();
}
