#include "settings.h"
#include "ui_settings.h"
#include <QColor>
#include <QColorDialog>

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
{
    memcpy(reinterpret_cast<void*>(settings_parent),reinterpret_cast<void*>(&sett),sizeof (SETTINGS));
    parentWidget()->repaint();
}
