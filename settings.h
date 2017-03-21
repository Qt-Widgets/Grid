#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

struct SETTINGS{
    QColor color_default;
    QColor color_act;
    QColor color_border;
    int border_width;
};

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0,struct SETTINGS * set = NULL);
    ~Settings();

private slots:
    void on_change_def_color_clicked();
    void on_change_act_color_clicked();
    void on_change_border_color_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Settings *ui;
    struct SETTINGS sett;
    struct SETTINGS *settings_parent;

};

#endif // SETTINGS_H
