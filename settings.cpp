#include "settings.h"
#include "ui_settings.h"
#include <QColor>
#include <QColorDialog>
#include <QMessageBox>

Settings::Settings(QWidget *parent,struct SETTINGS *set) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    settings_parent = set;
    memcpy(reinterpret_cast<void*>(&sett),reinterpret_cast<void*>(settings_parent),sizeof (SETTINGS));
//    sett.border_width = 1;
//    sett.color_act = QColor(Qt::green);
//    sett.color_border = QColor(Qt::black);
//    sett.color_default = QColor(Qt::gray);
    ui->border_color->setStyleSheet(QString("QLabel{background:rgb(%1,%2,%3)}").arg(sett.color_border.red()).arg(sett.color_border.green()).arg(sett.color_border.blue()));
    ui->default_color->setStyleSheet(QString("QLabel{background:rgb(%1,%2,%3)}").arg(sett.color_default.red()).arg(sett.color_default.green()).arg(sett.color_default.blue()));
    ui->active_color->setStyleSheet(QString("QLabel{background:rgb(%1,%2,%3)}").arg(sett.color_act.red()).arg(sett.color_act.green()).arg(sett.color_act.blue()));
    ui->border_width->setValue(sett.border_width);
    ui->fild_width->setValue(sett.fild_width);
    ui->fild_height->setValue(sett.fild_height);
    ui->squere_height->setValue(sett.squere_height);
    ui->squere_width->setValue(sett.squere_width);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_change_def_color_clicked()
{
    QColor color = QColorDialog::getColor(sett.color_default,this,"GetColor");
    if (color.isValid())sett.color_default = color;
    ui->default_color->setStyleSheet(QString("QLabel{background:rgb(%1,%2,%3)}").arg(sett.color_default.red()).arg(sett.color_default.green()).arg(sett.color_default.blue()));
}

void Settings::on_change_act_color_clicked()
{
    QColor color = QColorDialog::getColor(sett.color_act,this,"GetColor");
    if (color.isValid())sett.color_act = color;
    ui->active_color->setStyleSheet(QString("QLabel{background:rgb(%1,%2,%3)}").arg(sett.color_act.red()).arg(sett.color_act.green()).arg(sett.color_act.blue()));
}

void Settings::on_change_border_color_clicked()
{
    QColor color = QColorDialog::getColor(sett.color_border,this,"GetColor");
    if (color.isValid())sett.color_border = color;
    ui->border_color->setStyleSheet(QString("QLabel{background:rgb(%1,%2,%3)}").arg(sett.color_border.red()).arg(sett.color_border.green()).arg(sett.color_border.blue()));
}

void Settings::on_buttonBox_accepted()
{   if (sett.squere_height != ui->squere_height->value()||
        sett.squere_width != ui->squere_width->value()  ||
        sett.fild_height != ui->fild_height->value()    ||
        sett.fild_width != ui->fild_width->value()    ){
        QMessageBox error(QMessageBox::Information,
                                             "Warning","You must restart program for apply changed settings",
                                             QMessageBox::Ok,this);
        error.exec();
    }
    sett.squere_height = ui->squere_height->value();
    sett.squere_width = ui->squere_width->value();
    sett.fild_height = ui->fild_height->value();
    sett.fild_width = ui->fild_width->value();
    sett.border_width = ui->border_width->value();
    memcpy(reinterpret_cast<void*>(settings_parent),reinterpret_cast<void*>(&sett),sizeof (SETTINGS));
    parentWidget()->repaint();

}
