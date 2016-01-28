#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newsizechoice.h"
#include "colorchoicewindow.h"
#include <vector>

struct pixelBlock{
    QColor color;
    int xStart;
    int yStart;
    int xLength;
    int yLength;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int winHeight;
    int winWidth;
    int widthSpace;
    int heightSpace;
    QColor selectedCol;

private slots:
    void on_action_Open_triggered();

    void on_action_New_triggered();

public slots:
    void changeSize(int width, int height);
    int rectCollision(int x, int y);
    void changeColor(QColor color);

protected:
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    NewSizeChoice *newChoiceWindow;
    ColorChoiceWindow *newColorWindow;
};

#endif // MAINWINDOW_H
