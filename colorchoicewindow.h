#ifndef COLORCHOICEWINDOW_H
#define COLORCHOICEWINDOW_H

#include <QWidget>

namespace Ui {
class ColorChoiceWindow;
}

class ColorChoiceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ColorChoiceWindow(QWidget *parent = 0);
    ~ColorChoiceWindow();

private:
    Ui::ColorChoiceWindow *ui;
};

#endif // COLORCHOICEWINDOW_H
