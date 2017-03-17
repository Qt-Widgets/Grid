#ifndef SQUERE_H
#define SQUERE_H

#include <QWidget>
#include <QMouseEvent>



#define SIZE 32

enum Desc{TOP,LEFT,BOTTOM,RIGHT,CLICKED};

struct Description{
    bool top;
    bool left;
    bool bottom;
    bool right;
    bool clicked;
};

class Squere : public QWidget
{
    Q_OBJECT
public:
    Squere(QWidget *parent = 0);
    void changeDescription(int pos, bool state);
    bool getDeskClicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *pe);
    struct Description desc;

signals:
    void clicked(QString name_obj);
};

#endif // SQUERE_H
