#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGridLayout"
#include <QKeyEvent>

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

    void keyPressEvent(QKeyEvent * event);

private slots:
    void clickSquere(QString name_obj);
};

#endif // MAINWINDOW_H
