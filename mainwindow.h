#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newsizechoice.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Open_triggered();

    void on_action_New_triggered();

public slots:
    void changeSize(int width, int height);


private:
    Ui::MainWindow *ui;
    NewSizeChoice *newChoiceWindow;
};

#endif // MAINWINDOW_H
