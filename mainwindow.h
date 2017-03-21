#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGridLayout"
#include <QKeyEvent>
#include <QSettings>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout *lay;
    int num_row, num_col;
    QStringList *history_list;
    struct SETTINGS *settings;
    void keyPressEvent(QKeyEvent * event);
    QSettings saved_settings;

private slots:
    void clickSquere(QString name_obj);
    void showSettings();
    void saveSettings();
    void loadSettings();
    QString colorToString(QColor *color);
    QColor *stringToColor(QString string);
    void makeFild();
};

#endif // MAINWINDOW_H
