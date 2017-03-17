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
    for (int i = 0; i<n.height()/SIZE;i++){
        for (int j = 0; j<n.width()/SIZE; j++){
            Squere *s = new Squere(this);
            s->setObjectName(QString("%1:%2").arg(i).arg(j));
            lay->addWidget(s,i,j,1,1,Qt::AlignCenter);
            connect(s,SIGNAL(clicked(QString)),SLOT(clickSquere(QString)));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::clickSquere(QString name_obj){
    QStringList list = name_obj.split(':');
    int row = list.first().toInt();
    int column = list.last().toInt();
    Squere *s = this->findChild<Squere*>(name_obj);
    s->changeDescription(CLICKED,true);
}
