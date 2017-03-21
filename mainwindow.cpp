#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "squere.h"
#include "QScreen"
#include "QHBoxLayout"
#include "QLabel"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    saved_settings("MyOwnCompany","Grid")
{

    settings = new struct SETTINGS();
    loadSettings();

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
            Squere *s = new Squere(this,settings);
            s->setObjectName(QString("%1:%2").arg(i).arg(j));
            lay->addWidget(s,i,j,1,1,Qt::AlignCenter);
            connect(s,SIGNAL(clicked(QString)),SLOT(clickSquere(QString)));
        }
    }
    history_list = new QStringList();
    connect(ui->actionSettings,SIGNAL(triggered()),SLOT(showSettings()));

}

MainWindow::~MainWindow()
{
    saveSettings();
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

void MainWindow::showSettings(){
    Settings *settings = new Settings(this,this->settings);
    settings->show();
}

void MainWindow::saveSettings(){
    saved_settings.beginGroup("/settings");
        saved_settings.setValue("/default_color",colorToString(&settings->color_default));
        saved_settings.setValue("/active_color",colorToString(&settings->color_act));
        saved_settings.setValue("/border_color",colorToString(&settings->color_border));
        saved_settings.setValue("/border_width",QString::number(settings->border_width));
    saved_settings.endGroup();
}

void MainWindow::loadSettings(){
    saved_settings.beginGroup("/settings");
        settings->color_default = QColor(*stringToColor(saved_settings.value("/default_color","125:125:125").toString()));
        settings->color_act = QColor(*stringToColor(saved_settings.value("/active_color","0:255:0").toString()));
        settings->color_border = QColor(*stringToColor(saved_settings.value("/border_color","0:0:0").toString()));
        settings->border_width = saved_settings.value("/border_width",1).toInt();
    saved_settings.endGroup();
}

QColor* MainWindow::stringToColor(QString string){
    QColor *color = new QColor();
    QStringList list = string.split(':');
    color->setRed(list.at(0).toInt());
    color->setGreen(list.at(1).toInt());
    color->setBlue(list.at(2).toInt());
    return color;
}

QString MainWindow::colorToString(QColor *color){
    return QString("%1:%2:%3").arg(color->red()).arg(color->green()).arg(color->blue());
}
